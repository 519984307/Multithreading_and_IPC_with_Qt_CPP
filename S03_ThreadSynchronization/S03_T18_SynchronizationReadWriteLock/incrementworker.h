#ifndef INCREMENTWORKER_H
#define INCREMENTWORKER_H

#include <QThread>

#include "printdevice.h"

class IncrementWorker : public QThread
{
    Q_OBJECT
public:
    explicit IncrementWorker(PrintDevice* printDevice, bool* stop, QObject *parent = nullptr);

signals:

private:
    PrintDevice* m_printDevice = nullptr;
    bool* m_stop = nullptr;

    // QThread interface
protected:
    virtual void run() override;
};

#endif // INCREMENTWORKER_H
