#ifndef PRINTWORKER_H
#define PRINTWORKER_H

#include <QThread>

#include "printdevice.h"

class PrintWorker : public QThread
{
    Q_OBJECT
public:
    explicit PrintWorker(const QString& name, bool* stop, PrintDevice* printDevice, QObject *parent = nullptr);

signals:

    // QThread interface
protected:
    virtual void run() override;

private:
    QString m_name;
    bool* m_stop = nullptr;
    PrintDevice* m_printDevice = nullptr;
};

#endif // PRINTWORKER_H
