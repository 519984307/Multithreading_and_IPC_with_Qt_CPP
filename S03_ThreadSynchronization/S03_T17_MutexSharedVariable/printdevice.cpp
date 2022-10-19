#include "printdevice.h"

#include <QDebug>


PrintDevice::PrintDevice()
{

}

void PrintDevice::print(const QString text)
{
    QMutexLocker locker(&m_mutex);
    qDebug() << text << "Called, count : " << m_count++;
}
