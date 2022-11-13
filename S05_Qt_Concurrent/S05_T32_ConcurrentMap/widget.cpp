#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QtConcurrent>
#include <QThread>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    for (int i = 0; i < 10000; i++) {
        list << i;
    }

    qDebug() << "Original last value in the list : " << list.last();

    connect(&futureWatcher, &QFutureWatcher<void>::started, [=]() {
        qDebug() << "asynchronous : work started";
    });

    connect(&futureWatcher, &QFutureWatcher<void>::finished, [=]() {
        qDebug() << "asynchronous : work finished";
    });

    connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged, [=](int value) {
        qDebug() << "Progress : " << value;
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::modify(int &value)
{
    qDebug() << "Modifying " << value << " result : " << value * 10
             << " Thread : " << QThread::currentThread();
    value = value * 10;
}


void Widget::on_modify_pushButton_clicked()
{
    /*
    // Lambda function example
    auto modify = [](int &value) {
        qDebug() << "Modifying " << value << " result : " << value * 10
                 << " Thread : " << QThread::currentThread();
        value = value * 10;
    };
    */

    // Static method example

    future = QtConcurrent::map(list, modify);
    futureWatcher.setFuture(future);
}


void Widget::on_seeValue_pushButton_clicked()
{
    qDebug() << "Modified value : " << list.last();
}



void Widget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    future.cancel();
}
