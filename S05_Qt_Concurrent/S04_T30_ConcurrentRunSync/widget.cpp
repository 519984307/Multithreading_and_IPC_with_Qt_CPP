#include "widget.h"
#include "ui_widget.h"

#include <QtConcurrent>
#include <QDebug>
#include <QThread>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "Ui thread : " << QThread::currentThread();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::heavyWork()
{
    qDebug() << "Widget::heavyWork running in thread : " << QThread::currentThread();

    int upper = 10E8;
    int progressUpdateSteps = 100;

    for (int i = 0; i < upper; i++) {
        if (i % (upper / progressUpdateSteps) == 0) {
            double percentage = (i * 1.0 / upper) * 100; // Multiply by 1.0 to convert i to a double.
            qDebug() << "Percentage : " << QVariant(percentage).toInt() << " Calcuated in thread : " << QThread::currentThread();
        }
    }
}


void Widget::on_start_pushButton_clicked()
{
    future = QtConcurrent::run(heavyWork);

    future.waitForFinished(); // Blocks the user interface

    qDebug() << "Computation finished.";
}


void Widget::on_cancel_pushButton_clicked()
{
    future.cancel(); // Does not work for QtConcurrent::run
}


void Widget::on_pause_pushButton_clicked()
{
    // QFuture::pause, demonstrated in the tutorial, is deprecated, using QFuture::suspend instead.
    future.suspend(); // Does not work for QtConcurrent::run
}


void Widget::on_resume_pushButton_clicked()
{
    future.resume(); // Does not work for QtConcurrent::run
}

