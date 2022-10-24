#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QSemaphore>
#include <QVector>

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

    bool atEnd = false;
    QSemaphore* freeSpace = nullptr;
    QSemaphore* availableSpace = nullptr;
    QVector<int> dataSource;
    int bufferArray[BUFFER_SIZE];
    Producer* producer;
    Consumer* consumer;
};
#endif // WIDGET_H
