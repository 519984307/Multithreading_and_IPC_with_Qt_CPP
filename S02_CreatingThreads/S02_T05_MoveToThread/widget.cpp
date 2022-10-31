#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#include "worker.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "Widget constructor running in the gui thread : " << thread();
    qDebug() << "Current thread in Widget constructor : " << QThread::currentThread();

    workerThread = new QThread(this);
    connect(workerThread, &QThread::finished, this, &Widget::threadFinished);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_start_pushButton_clicked()
{
    // Instance of Worker created in the Main thread
    Worker * worker = new Worker(); // TODO ADD DELETE

    // Instance of Worker moved to the workerThread
    worker->moveToThread(workerThread);

    connect(workerThread, &QThread::started, worker, &Worker::doCounting);
    connect(workerThread, &QThread::finished, worker, &Worker::deleteLater);
    connect(worker, &Worker::currentCount, this, &Widget::currentCount);
    connect(worker, &Worker::countDone, this, &Widget::countDone);

    workerThread->start();
}


void Widget::on_information_pushButton_clicked()
{
    qDebug() << "Thread running : " << workerThread->isRunning();
}

void Widget::countDone()
{
    qDebug() << "Widget, count done";
    workerThread->exit(); // Kill the thread explicityly, otherwise it is still running its event loop.
    workerThread = nullptr;
}

void Widget::currentCount(int value)
{
    ui->progressBar->setValue(value);
    ui->info_label->setText(QString::number(value));
}

void Widget::threadFinished()
{
    qDebug() << "Thread finished. Thread : " << thread();
    qDebug() << "Thread finished. Current Thread : " << QThread::currentThread();
}

void Widget::closeEvent(QCloseEvent *event)
{
    // Monday 3rd October 2022
    // The tutorial implementation results in a crash if the user tries to quit the application before the workerThread has finished.

    qDebug() << "closeEvent method called";
    workerThread->quit();

    /*
    // If the application is closed before the workerThread has completed then quit the workerThread to prevent the application crashing on exit
    if (workerThread) {
        qDebug() << "Attempting to end the workerThread";
       //  workerThread->requestInterruption(); // This is handled in void Worker::doCounting()
        workerThread->exit();
    }
    */
}
