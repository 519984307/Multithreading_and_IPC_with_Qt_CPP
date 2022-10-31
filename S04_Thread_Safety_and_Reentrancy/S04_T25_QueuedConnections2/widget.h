#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <Thread>

#include "producer.h"
#include "consumer.h"
#include "thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;

private:
    Ui::Widget *ui;

    Producer* producer = nullptr;
    Consumer* consumer = nullptr;
    Thread* thread = nullptr;

};
#endif // WIDGET_H
