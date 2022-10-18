#ifndef PRINTWORKER_H
#define PRINTWORKER_H

#include <QMutex>
#include <QThread>

class PrintWorker : public QThread
{
    Q_OBJECT
public:
    explicit PrintWorker(QString name, bool* stop, QMutex* mutex, QObject *parent = nullptr);
    ~PrintWorker();

signals:


    // QThread interface
protected:
    virtual void run() override;

    QString m_name;
    bool* m_stop; // Shared between objects / threads
    QMutex* m_mutex; // Shared between objects / threads
};

#endif // PRINTWORKER_H
