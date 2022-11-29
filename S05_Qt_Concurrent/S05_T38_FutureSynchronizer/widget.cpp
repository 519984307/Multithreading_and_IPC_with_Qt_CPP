#include "widget.h"
#include "ui_widget.h"

#include <QtConcurrent>
#include <QFutureSynchronizer>
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

     filterValue = ui->filter_spinBox->value();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::reduce(int &sum, int value)
{
    sum += value;
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

    QFutureSynchronizer<int> synchronizer;

    ui->filteredList_listWidget->clear();

    future = QtConcurrent::filtered(intList, filter);
    QFuture<int> futureReduce = QtConcurrent::filteredReduced(intList, filter, reduce);

    // Synchronous
    synchronizer.addFuture(future);
    synchronizer.addFuture(futureReduce);

    // The following line is my addition, it is not in the tutorial, but having read the documentation I believe that it is necessary.
    synchronizer.waitForFinished();

    QList<int> newList = future.results();

    for (int item: newList) {
        ui->filteredList_listWidget->addItem(QString::number(item));
    }

    qDebug() << "Item count after filtering : " << newList.count();



    qDebug() << "The sum is : " << futureReduce.result();
    ui->sum_label->setText(QString::number(futureReduce.result()));
}


void Widget::on_filter_spinBox_valueChanged(int arg1)
{
    filterValue = arg1;
}

