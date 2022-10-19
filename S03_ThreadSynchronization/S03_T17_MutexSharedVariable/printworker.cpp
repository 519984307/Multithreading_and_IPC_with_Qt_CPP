#include "printworker.h"

PrintWorker::PrintWorker(QString name, bool* stop, PrintDevice* printDevice, QObject *parent)
    : QThread{parent}, m_name(name), m_stop(stop), m_printDevice(printDevice)
{

}


void PrintWorker::run()
{
    while(!*m_stop) {
        m_printDevice->print(m_name);
        sleep(1);
    }
}
