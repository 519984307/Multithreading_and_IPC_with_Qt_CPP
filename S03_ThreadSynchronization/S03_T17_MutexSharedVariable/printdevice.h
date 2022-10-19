#ifndef PRINTDEVICE_H
#define PRINTDEVICE_H

#include <QMutex>
#include <QString>


class PrintDevice
{
public:
    PrintDevice();

public:
    void print(const QString text);

private:
    int m_count = 0;
    QMutex m_mutex;
};

#endif // PRINTDEVICE_H
