#ifndef PRINTDEVICE_H
#define PRINTDEVICE_H

#include <QReadWriteLock>
#include <QString>


class PrintDevice
{
public:
    PrintDevice();

public:
    void print(const QString& text);
    void increment();

private:
    int m_count = 0;
    QReadWriteLock m_readWriteLock;
};

#endif // PRINTDEVICE_H
