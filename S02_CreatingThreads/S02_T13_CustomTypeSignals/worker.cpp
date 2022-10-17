#include "worker.h"

#include <QDebug>
#include <QThread>
#include <QVariant>

Worker::Worker(QObject *parent) : QObject{parent}
{
    qDebug() << "Worker constructor running in thread : " << QThread::currentThread();
}

Worker::~Worker()
{
    qDebug() << "Worker destroyed, destructor running in thread : " << QThread::currentThread();
}

void Worker::doCounting()
{
    // Code in this method will run in a secondary/background thread
    qDebug() << "Worker doCounting method running in thread : " << QThread::currentThread();

    int upper = 1E8;
    int progressUpdateSteps = 100;

    for (int i{0}; i < upper; i++) {
        double percentage = (i * 1.0 / upper) * 100;

        // qDebug() << "Percentage : " << percentage;

        if (i % (upper / (upper / progressUpdateSteps)) == 0) {
            // Monday 3rd October 2022
            // The tutorial implementation results in a crash if the user tries to quit the application before the workerThread has finished.
            // The following if statement exits the loop if an interruption of the thread is requested.
            // The method QThread::requestInterruption() is called in Widget::closeEvent(QCloseEvent *event) and handled in the if statement below.
            if (thread()->isInterruptionRequested()) {
                break;
            }

            QString txt = "Hello " + QString::number(QVariant::fromValue(percentage).toInt());
            NumberedString ns(QVariant::fromValue(percentage).toInt(), txt);

            emit currentCount(QVariant::fromValue(percentage).toInt());
            emit currentNumberedString(ns);
        }
    }

    emit countDone();
}
