#include <QApplication>

#include <QDebug>
#include <QMutex>
#include <QMessageBox>

#include "printworker.h"

#include <iostream> // Not used in the tutorial, but works as expected!

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Hello World!\nFrom S03_T16_ThreadSynchronizationMutex";

    std::cout << "Hello World! from iostream";

    bool stopFlag = false;
    QMutex mutex;

    PrintWorker black("Black", &stopFlag, &mutex), white("White", &stopFlag, &mutex);

    black.start();
    white.start();

    // The QMessageBox effectively blocks the gui thread until the user presses the OK button.
    QMessageBox::information(nullptr, "QMutex", "Thread working, close me to stop");

    stopFlag = true;

    black.wait();
    white.wait();

    return 0;
}
