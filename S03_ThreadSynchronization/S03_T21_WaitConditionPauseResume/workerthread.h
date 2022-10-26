#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

#include <QMutex>
#include <QWaitCondition>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = nullptr);
    ~WorkerThread();

signals:
    void currentCount(int value);

public slots:
    void pause();
    void resume();

    // QThread interface
protected:
    virtual void run() override;

private:
    QMutex m_mutex;
    QWaitCondition m_pause_condition;
    bool m_pause = false;
};

#endif // WORKERTHREAD_H
