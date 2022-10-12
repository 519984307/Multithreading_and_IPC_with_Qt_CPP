#include "worker.h"

#include <QDebug>
#include <QThread>

Worker::Worker() : QRunnable()
{
    qDebug() << "Worker constructor running in thread : " << QThread::currentThread();
}

Worker::~Worker()
{
    qDebug() << "Worker destructor running in thread : " << QThread::currentThread();
}


void Worker::run()
{
    int loopIterations = 1E9;
    int progressSteps = 100;

    for (int i{0}; i < loopIterations; i++) {

        if (i % (loopIterations / progressSteps) == 0) {

            double percentage = (i * 100.0 / loopIterations);
            qDebug() << "Current percentage : " << percentage;
        }
    }
}
