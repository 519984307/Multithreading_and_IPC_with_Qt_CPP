#include "workerthread.h"

#include <QDebug>
#include <QTimer>

WorkerThread::WorkerThread(QObject *parent) : QThread{parent}
{
    qDebug() << "WorkerThread constructor running in thread : " << QThread::currentThread();
}

WorkerThread::~WorkerThread()
{
    qDebug() << "WorkerThread destructor running in thread : " << QThread::currentThread();
}


void WorkerThread::run()
{
    qDebug() << "WorkerThread run method running in thread : " << QThread::currentThread();

    QTimer * timer = new QTimer();

    connect(timer, &QTimer::timeout, []() {
        qDebug() << "Timer timed out. Timer running in thread : " << QThread::currentThread();
    });
    timer->setInterval(1000);
    timer->start();

    // Set up an event loop
    exec();
}
