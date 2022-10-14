#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QEvent>
#include <QThreadPool>

#include "progressevent.h"
#include "worker.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "ui thread running in : " << QThread::currentThread();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::gotUpdate(int value)
{
    ui->progressBar->setValue(value);
}


void Widget::on_start_pushButton_clicked()
{
    Worker * worker = new Worker(this);

    // If the auto-deletion flag is set to true then Qt manages the memory, otherwise the memory allocated to the instance of Worker needs to be release.
    // worker->setAutoDelete(false);

    QThreadPool::globalInstance()->start(worker);
}


void Widget::on_information_pushButton_clicked()
{
    qDebug() << "QThread::idealThreadCount : " << QThread::idealThreadCount();
    qDebug() << "QThreadPool::globalInstance::maxThreadCount : " << QThreadPool::globalInstance()->maxThreadCount();
}



bool Widget::event(QEvent *event)
{
    if (event->type() == static_cast<QEvent::Type>(ProgressEvent::EventID)) {
        ProgressEvent* progressEvent = static_cast<ProgressEvent*>(event);

        qDebug() << "Widget progress is : " << progressEvent->progress();
        ui->progressBar->setValue(progressEvent->progress());
    }

    return QWidget::event(event);
}
