#include <QApplication>

#include <QMessageBox>

#include "printdevice.h"
#include "printworker.h"
#include "incrementworker.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool stopFlag = false;

    PrintDevice printDevice;

    PrintWorker black("Black", &stopFlag, &printDevice);
    PrintWorker white("White", &stopFlag, &printDevice);
    IncrementWorker incrementWorker(&printDevice, &stopFlag);

    black.start();
    white.start();
    incrementWorker.start();

    QMessageBox::information(nullptr, "QMutex", "Thread working. Close me to stop.");

    stopFlag = true;

    black.wait();
    white.wait();
    incrementWorker.wait();

    return 0;
}
