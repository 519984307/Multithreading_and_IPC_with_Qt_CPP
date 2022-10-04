#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QThread>

#include "workerthread.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "ui thread : " << QThread::currentThread();

    workerThread = new WorkerThread(this);
    connect(workerThread, &WorkerThread::currentCount, this, &Widget::currentCount);
    connect(workerThread, &WorkerThread::started, []() {
        qDebug() << "Thread started";
    });
    connect(workerThread, &WorkerThread::finished, []() {
        qDebug() << "Thread finished";
    });
}

Widget::~Widget()
{
    qDebug() << "Widget destructor running in thread : " << QThread::currentThread();

    delete ui;
}


void Widget::on_start_pushButton_clicked()
{
    workerThread->start();
}


void Widget::on_information_pushButton_clicked()
{
    qDebug() << "Thread running status: " << workerThread->isRunning();
}

void Widget::currentCount(int value)
{
    ui->progressBar->setValue(value);
    ui->information_label->setText(QString::number(value));
}
