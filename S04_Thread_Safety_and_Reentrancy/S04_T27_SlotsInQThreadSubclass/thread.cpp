#include "thread.h"

#include <QDebug>

Thread::Thread(QObject *parent)
    : QThread{parent},
      m_count(0)
{
    qDebug() << "Constructor running in thread : " << QThread::currentThread();
}

void Thread::incrementCount()
{
    // This method runs in the GUI thread, not the managed thread.

    qDebug() << "Thread::incrementCount called in thread : " << QThread::currentThread();
    ++m_count;

    if (m_count == 5) {
        m_timer->stop();
        thread()->quit();
    }

}

void Thread::run()
{
    // Managed thread, the m_Timer affinity is with the managed thread.

    qDebug() << "Thread::run called in thread : " << QThread::currentThread();
    m_timer = new QTimer(); // The timer lives in the managed thread, not the Ui thread.
    connect(m_timer, &QTimer::timeout, this, &Thread::incrementCount);
    m_timer->start(1000);

    exec(); // Start an event loop, otherwise the timer will not work.
}
