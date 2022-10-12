#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    thread = new WorkerThread(this);

    connect(thread, &WorkerThread::finished, []() {
        qDebug() << "Thread finished";
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_start_pushButton_clicked()
{
    thread->start();
}


void Widget::on_stop_pushButton_clicked()
{
    thread->exit();
}


void Widget::on_information_pushButton_clicked()
{
    qDebug() << "Thread running : " << thread->isRunning();
}



void Widget::closeEvent(QCloseEvent *event)
{
    thread->exit();
}
