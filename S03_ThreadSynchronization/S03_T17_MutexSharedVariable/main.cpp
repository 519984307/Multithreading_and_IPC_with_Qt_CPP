#include <QApplication>

#include <QMessageBox>

#include "printworker.h"
#include "printdevice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool stopFlag = false;
    PrintDevice printDevice;

    PrintWorker black("Black", &stopFlag, &printDevice);
    PrintWorker white("White", &stopFlag, &printDevice);

    black.start();
    white.start();

    QMessageBox::information(nullptr, "QMutex", "Thread working, close me to stop");

    stopFlag = true;

    black.wait();
    white.wait();

    return 0;
}
