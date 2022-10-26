#include "workerthread.h"

#include <QDebug>
#include <QVariant>


WorkerThread::WorkerThread(QObject *parent)
    : QThread{parent}
{
    m_pause = false;
}

WorkerThread::~WorkerThread()
{
    qDebug() << "WorkerThread instance destroyed in thread : " << QThread::currentThread();
}

void WorkerThread::pause()
{
    qDebug() << "Pause method, WorkerThread::pause running in thread : " << QThread::currentThread();

    m_mutex.lock();

    m_pause = true;

    m_mutex.unlock();
}

void WorkerThread::resume()
{
    qDebug() << "Resume method, WorkerThread::resume, running in thread : " << QThread::currentThread();

    m_mutex.lock();

    m_pause = false;

    m_mutex.unlock();

    m_pause_condition.wakeAll();
}


void WorkerThread::run()
{
    qDebug() << "Run method, WorkerThread::run, running in thread : " << QThread::currentThread();

    int upper = 1E8;
    int progressUpdateSteps = 100;

    for (int i{0}; i < upper; i++) {

        m_mutex.lock();

        if (m_pause) {
            m_pause_condition.wait(&m_mutex); // Freeze code execution in this thread
        }

        m_mutex.unlock();

        double percentage = (i * 1.0 / upper) * 100;

        // qDebug() << "Percentage : " << percentage;

        if (i % (upper / (upper / progressUpdateSteps)) == 0) {
            // Monday 3rd October 2022
            // The tutorial implementation results in a crash if the user tries to quit the application before the workerThread has finished.
            // The following if statement exits the loop if an interruption of the thread is requested.
            // The method QThread::requestInterruption() is called in Widget::closeEvent(QCloseEvent *event) and handled in the if statement below.
            if (thread()->isInterruptionRequested()) {
                qDebug() << "WorkerThread::run : Interrupting the thread";
                break;
            }
            emit currentCount(QVariant::fromValue(percentage).toInt());
        }
    }
}
