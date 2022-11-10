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

    qDebug() << "Ui thread : " << QThread::currentThread();

    connect(&watcher, &QFutureWatcher<void>::finished, [=]() {
        qDebug() << "--------------------Computation done--------------------";

        if (!watcher.isCanceled()) {
            QVector<int> resultVector = watcher.result();

            qDebug() << "Number of items in resultVector : "
                     << resultVector.count();

            for (int i = 0; i < resultVector.length(); i++) {
                qDebug() << "element[" << i << "]" << resultVector.at(i);
            }
        } else {
            qDebug() << "Watcher already cancelled";
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

QFuture<QVector<int> > Widget::heavyWorkWithReturn()
{
    qDebug() << "Widget::heavyWorkWithReturn running in thread : " << QThread::currentThread();

    auto heavyWork = [=]() {
        QVector<int> intVector;

        int upper = 10E8 +1;
        int progressUpdateSteps = 100;

        for (int i = 0; i < upper; i++) {
            if (i % (upper / progressUpdateSteps) == 0) {
                double percentage = (i * 1.0 / upper) * 100; // Multiply by 1.0 to convert i to a double.
                qDebug() << "Percentage : " << QVariant(percentage).toInt() << " Calcuated in thread : " << QThread::currentThread();
                intVector.push_back(QVariant(percentage).toInt());
            }
        }
        return intVector;
    };

    return QtConcurrent::run(heavyWork);
}


void Widget::on_start_pushButton_clicked()
{
    future =  heavyWorkWithReturn();

    watcher.setFuture(future);
}


void Widget::on_cancel_pushButton_clicked()
{
    watcher.cancel(); // Causes a crash, as the application tries to get values from a futures that has been cancelled.
}


void Widget::on_pause_pushButton_clicked()
{
    // pause() used in the tutorial demonstration is deprecated in Qt 6.0, it has been replaced by suspend() which does not work with the QFuture returned by QtConcurrent::run()
    watcher.suspend();
}


void Widget::on_resume_pushButton_clicked()
{
    watcher.resume();
}

