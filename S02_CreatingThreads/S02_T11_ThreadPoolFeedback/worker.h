#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QRunnable>

class Worker : public QRunnable
{
public:
    Worker(QObject* receiver);
    ~Worker() override;

    // QRunnable interface
public:
    virtual void run() override;

private:
    QObject* m_receiver = nullptr;
};

#endif // WORKER_H
