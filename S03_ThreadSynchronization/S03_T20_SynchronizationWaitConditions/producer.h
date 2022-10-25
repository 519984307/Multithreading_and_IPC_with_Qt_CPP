#ifndef PRODUCER_H
#define PRODUCER_H

#include <QThread>

#include <QMutex>
#include <QWaitCondition>


class Producer : public QThread
{
    Q_OBJECT
public:
    explicit Producer(char * buffer, int bufferSize, int * usedSlots, int totalData,
                      QMutex* mutex, QWaitCondition* bufferFull, QWaitCondition* bufferEmpty, QObject *parent = nullptr);

signals:


    // QThread interface
protected:
    virtual void run() override;

private:
    char* m_buffer = nullptr;
    int m_buffer_size;
    int* m_used_slots = nullptr;
    int m_total_data;
    QMutex* m_mutex = nullptr;
    QWaitCondition* m_buffer_full = nullptr;
    QWaitCondition* m_buffer_empty = nullptr;
};

#endif // PRODUCER_H
