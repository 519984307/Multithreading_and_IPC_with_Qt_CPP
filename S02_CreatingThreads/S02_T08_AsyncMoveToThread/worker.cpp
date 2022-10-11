#include "worker.h"

#include <QDebug>
#include <QTimer>
#include <QThread>

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

Worker::~Worker()
{
    qDebug() << "Worker Destructor running in thread: " << QThread::currentThread();
}



void Worker::doWork()
{
    QTimer * timer = new QTimer();

    connect(timer, &QTimer::timeout, []() {
        qDebug() << "Timer timed out. Timer running in thread : " << QThread::currentThread();
    });
    timer->setInterval(1000);
    timer->start();
}
