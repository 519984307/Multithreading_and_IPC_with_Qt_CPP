#include "worker.h"

#include <QApplication>
#include <QDebug>
#include <QThread>
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
    int loopIterations = 1E9;
    int progressSteps = 100;

    for (int i{0}; i < loopIterations; i++) {

        if (i % (loopIterations / progressSteps) == 0) {

            double percentage = (i * 100.0 / loopIterations);
            // qDebug() << "Current percentage : " << percentage;
            QApplication::postEvent(m_receiver, new ProgressEvent(QVariant::fromValue(percentage).toInt()));
        }
    }
}
