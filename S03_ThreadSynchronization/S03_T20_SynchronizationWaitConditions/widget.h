#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QMutex>
#include <QWaitCondition>

#include "producer.h"
#include "consumer.h"


const int BUFFER_SIZE = 6;


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_start_pushButton_clicked();

private:
    Ui::Widget *ui;

    int totalData;
    char buffer[BUFFER_SIZE];
    QWaitCondition bufferFull;
    QWaitCondition bufferEmpty;
    QMutex mutex;
    int usedSlots;
    Producer* producer = nullptr;
    Consumer* consumer = nullptr;
};
#endif // WIDGET_H
