#ifndef PRINTWORKER_H
#define PRINTWORKER_H

#include <QThread>

#include <QMutex>

#include "printdevice.h"


class PrintWorker : public QThread
{
    Q_OBJECT
public:
    explicit PrintWorker(QString name, bool* stop, PrintDevice* printDevice, QObject *parent = nullptr);

signals:

private:
    QString m_name;
    bool* m_stop = nullptr;
    PrintDevice* m_printDevice = nullptr;

    // QThread interface
protected:
    virtual void run() override;
};

#endif // PRINTWORKER_H
