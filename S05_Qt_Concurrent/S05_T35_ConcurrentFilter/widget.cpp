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
    });

    connect(&futureWatcher, &QFutureWatcher<void>::finished, this, [=]() {
        qDebug() << "asynchronous : Work finished.";
        qDebug() << "Modified list : " << intList;

        ui->filteredList_listWidget->clear();
        for (int item: intList) {
            ui->filteredList_listWidget->addItem(QString::number(item));
        }
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

    future = QtConcurrent::filter(intList, filter);

    // Synchonous version - comment out the line that sets the future on the futureWatcher
    /*
    future.waitForFinished();
    qDebug() << "synchronous : Work finished.";
    qDebug() << "Modified list : " << intList;

    ui->filteredList_listWidget->clear();
    for (int item: intList) {
        ui->filteredList_listWidget->addItem(QString::number(item));
    }
    */

    futureWatcher.setFuture(future);
}


void Widget::on_filter_spinBox_valueChanged(int arg1)
{
    filterValue = arg1;
}

