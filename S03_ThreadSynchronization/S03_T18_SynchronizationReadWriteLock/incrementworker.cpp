#include "incrementworker.h"

IncrementWorker::IncrementWorker(PrintDevice* printDevice, bool* stop, QObject *parent)
    : QThread{parent},
      m_printDevice{printDevice}, m_stop{stop}
{

}


void IncrementWorker::run()
{
    while (!(*m_stop)) {
        msleep(1500);
        m_printDevice->increment();
    }
}
