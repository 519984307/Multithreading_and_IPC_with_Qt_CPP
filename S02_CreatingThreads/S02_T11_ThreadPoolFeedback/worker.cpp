#include "worker.h"

#include <QApplication>
#include <QDebug>
#include <QMetaObject>
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

        if ((i +1) % (loopIterations / progressSteps) == 0) {

            double percentage = (i * 100.0 / loopIterations); // Without adding 1 to i the maximum percentage reported is 99%.
            // qDebug() << "Current percentage : " << percentage;

            /*
            // Sending feedback to the ui by subclass QEvent
            QApplication::postEvent(m_receiver, new ProgressEvent(QVariant::fromValue(percentage).toInt()));
            */

            // Sending feedback to the ui using QMetaObject::invokeMethod
            QMetaObject::invokeMethod(m_receiver, "gotUpdate", Qt::QueuedConnection, Q_ARG(int, QVariant::fromValue(percentage).toInt()));
        }
    }
}
