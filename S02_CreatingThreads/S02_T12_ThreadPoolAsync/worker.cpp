#include "worker.h"

#include <QApplication>
#include <QDebug>
#include <QMetaObject>
#include <QThread>
#include <QTimer>
#include <QVariant>

#include "progressevent.h"

Worker::Worker(QObject* receiver) : QRunnable(), m_receiver(receiver)
{
    qDebug() << "Worker constructor running in thread : " << QThread::currentThread();
}

Worker::~Worker()
{
    qDebug() << "Worker destructor running in thread : " << QThread::currentThread();
}


void Worker::run()
{
    qDebug() << "Worker::run() method running in thread : " << QThread::currentThread();

    //Because there is no event loop in the threads in here, you can't run async code like QTimer or TCPSocket.
    // If you do, the thread just exits and finishes without doing anything.

    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, []() {
        qDebug() << "Time out. Running in thread: " << QThread::currentThread();
    });

    timer->setInterval(1000);
    timer->start();
}
