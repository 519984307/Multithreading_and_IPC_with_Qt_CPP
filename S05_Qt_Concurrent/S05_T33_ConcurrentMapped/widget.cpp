#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QThread>
#include <QtConcurrent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Populate the list
    for (int i{0}; i < 30; i++) {
        list << i;
    }

    // Monitor work using QFutureWatcher
    connect(&futureWatcher, &QFutureWatcher<void>::started, [=]() {
       qDebug() << "asynchronous : Work started ";
    });

    connect(&futureWatcher, &QFutureWatcher<void>::finished, this, [=]() {
        qDebug() << "asynchronous : Work finished ";
        qDebug() << "Result count : " << future.resultCount();
        qDebug() << future.results();

        // Output the results using a loop
        for (int  i{0}; i < future.resultCount(); i++) {
            qDebug() << "Result " << i << " : " << future.resultAt(i);
        }
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_modify_pushButton_clicked()
{
    /*
    // Lambda function example
    std::function<int(const int &)> modify = [](const int & value) {
        qDebug() << "Modifying " << value << " result : " << value * 10 << " Thread : " << QThread::currentThread();
        return value * 10;
    };
    */

    future = QtConcurrent::mapped(list, modify);
    futureWatcher.setFuture(future);

    // Synchronous version - Uncomment the section below and increase the size of the list to demonstrate ui thread blocking
    /*
    future.waitForFinished();
    qDebug() << "synchronous : Work finished ";
    qDebug() << "Result count : " << future.resultCount();
    qDebug() << future.results();

    // Output the results using a loop
    for (int  i{0}; i < future.resultCount(); i++) {
        qDebug() << "Result " << i << " : " << future.resultAt(i);
    }
    */
}


void Widget::on_seeValues_pushButton_clicked()
{
    qDebug() << "Original values : " << list;
}

int Widget::modify(const int &value)
{
    qDebug() << "Modifying " << value << " result : " << value * 10 << " Thread : " << QThread::currentThread();
    return value * 10;
}



void Widget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    future.cancel();
}
