#include "thread.h"

#include "consumer.h"

Thread::Thread(Producer * producer, QObject *parent)
    : QThread{parent},
      m_producer(producer)
{

}


void Thread::run()
{
    Consumer consumer; // Create the instance of Consumer on the stack
    connect(m_producer, &Producer::data, &consumer, &Consumer::data); // Pass the address of the instance of Consumer on the stack

    // Start an event loop
    exec();
}
