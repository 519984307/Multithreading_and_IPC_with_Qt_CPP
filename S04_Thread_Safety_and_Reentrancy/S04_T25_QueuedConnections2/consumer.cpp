#include "consumer.h"

#include <QDebug>
#include <QThread>

Consumer::Consumer(QObject *parent)
    : QObject{parent}
{
    m_counter = 0;
}

void Consumer::data(const CustomData &cd)
{
    qDebug() << "Consumer message : " << cd.m_integer << cd.m_pointer << cd.m_string << " in thread : " << QThread::currentThread();

    // Kill the thread when the count reaches 10
    if (++m_counter > 10) {
        qDebug() << "Consumer thread about to be killed";
        thread()->quit();
    }

}
