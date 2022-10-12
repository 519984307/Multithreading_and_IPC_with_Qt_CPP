#ifndef WORKER_H
#define WORKER_H

#include <QRunnable>

class Worker : public QRunnable
{
public:
    Worker();
    ~Worker() override;

    // QRunnable interface
public:
    virtual void run() override;
};

#endif // WORKER_H
