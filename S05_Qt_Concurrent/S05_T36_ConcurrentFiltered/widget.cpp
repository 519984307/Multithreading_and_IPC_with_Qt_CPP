#include "widget.h"
#include "ui_widget.h"

#include <QtConcurrent>
#include <QThread>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "Ui thread : " << QThread::currentThread();

    // Populate intList with numbers
    for (int i{0}; i < 100; i++) {
        intList << QRandomGenerator::global()->bounded(1000);
    }

    qDebug() << "Before, item count : " << intList.count();

    // Clear List
    ui->originalList_listWidget->clear();
    ui->filteredList_listWidget->clear();

    for (int item: intList) {
        ui->originalList_listWidget->addItem(QString::number(item));
    }

    // Monitor work using QFutureWatcher
    connect(&futureWatcher, &QFutureWatcher<void>::started, [=]() {
       qDebug() << "asynchronous : Work started.";
       qDebug() << "Item count before filtering : " << intList.count();
    });

    connect(&futureWatcher, &QFutureWatcher<void>::finished, this, [=]() {
        qDebug() << "asynchronous : Work finished.";

        // Get the results and use them
        QList<int> newList = future.results();

        for (int item: newList) {
            ui->filteredList_listWidget->addItem(QString::number(item));
        }

        qDebug() << "Item count after filtering : " << newList.count();
    });

     filterValue = ui->filter_spinBox->value();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_filterButton_pushButton_clicked()
{
    auto filter = [=](const int value){
        if (value >= filterValue) {
            qDebug() << "Thread : " << QThread::currentThread() << ". Value " << value << " greater than " << filterValue;
            return false;
        } else {
            return true;
        }
    };

    ui->filteredList_listWidget->clear();

    future = QtConcurrent::filtered(intList, filter);

    // Synchronous version
    /*
    future.waitForFinished();

    QList<int> newList = future.results();

    for (int item: newList) {
        ui->filteredList_listWidget->addItem(QString::number(item));
    }

    qDebug() << "Item count after filtering : " << newList.count();
    */


    // Asynchronous version
    futureWatcher.setFuture(future);
}


void Widget::on_filter_spinBox_valueChanged(int arg1)
{
    filterValue = arg1;
}

