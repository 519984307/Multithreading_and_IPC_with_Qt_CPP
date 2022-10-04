#include "workerthread.h"

#include <QDebug>
#include <QVariant>

WorkerThread::WorkerThread(QObject *parent)
    : QThread{parent}
{
    qDebug() << "Worker thread constructor running in thread :" << QThread::currentThread();
}

WorkerThread::~WorkerThread()
{
    qDebug() << "Worker thread destructor running in thread :" << QThread::currentThread();
}


void WorkerThread::run()
{
    // Calling exec() here results in unexpected behavior.
    // exec();

    qDebug() << "Run method of workerThread running in thread :" << QThread::currentThread();

    int upper = 1E8;
    int progressUpdateSteps = 100;

    for (int i{0}; i < upper; i++) {
        double percentage = (i * 1.0 / upper) * 100;

        // qDebug() << "Percentage : " << percentage;

        if (i % (upper / (upper / progressUpdateSteps)) == 0) {

            emit currentCount(QVariant::fromValue(percentage).toInt());
        }
    }

    // Tutorial implementation : call exec() after the for loop to set up an event loop
    // exec();
}
