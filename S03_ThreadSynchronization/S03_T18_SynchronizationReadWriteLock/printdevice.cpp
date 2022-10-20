#include "printdevice.h"

#include <QDebug>


PrintDevice::PrintDevice() : m_count(0)
{

}

void PrintDevice::print(const QString &text)
{
    QReadLocker readLocker(&m_readWriteLock);

    qDebug() << text << "Called, count : " << m_count;
}

void PrintDevice::increment()
{
    QWriteLocker writeLocker(&m_readWriteLock);
    ++m_count;
}
