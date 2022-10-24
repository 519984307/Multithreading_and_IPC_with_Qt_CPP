#ifndef PRODUCER_H
#define PRODUCER_H

#include <QThread>

#include <QSemaphore>
#include <QVector>

class Producer : public QThread
{
    Q_OBJECT
public:
    explicit Producer(const QVector<int> & datasource, int* buffer, const int bufferSize,
                      QSemaphore* freeSpace, QSemaphore* availableSpace,
                      bool* atEnd, QObject *parent = nullptr);

signals:

    // QThread interface
protected:
    virtual void run() override;

private:
    QVector<int> m_data_source;
    int* m_buffer; // Pointer to an array of integers
    int m_BUFFER_SIZE;
    QSemaphore* m_free_space; // Space where the producer can write data
    QSemaphore* m_available_space; // Space where the consumer can read data from
    bool* m_at_end; // Set when the end of m_data_source is reached
};

#endif // PRODUCER_H
