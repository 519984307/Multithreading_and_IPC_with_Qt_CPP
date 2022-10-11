#include "widget.h"
#include "ui_widget.h"

#include <QThread>

#include "worker.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    thread = new QThread(this);

    // In the tutorial this connect statement is in the on_start_pushButton_clocked,
    // this results in multiple "Thread finished" messages if the thread is stopped and restarted.
    connect(thread, &QThread::finished, []() {
       qDebug() << "Thread finished: ";
    });

    qDebug() << "ui thread: " << QThread::currentThread();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_start_pushButton_clicked()
{
    Worker* worker = new Worker();

    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &Worker::doWork);
    connect(thread, &QThread::finished, worker, &Worker::deleteLater);

    thread->start();
}


void Widget::on_stop_pushButton_clicked()
{
    thread->exit();
}


void Widget::on_information_pushButton_clicked()
{
    qDebug() << "Thread is running : " << thread->isRunning();
}

void Widget::closeEvent(QCloseEvent *event)
{
    thread->exit();
}
