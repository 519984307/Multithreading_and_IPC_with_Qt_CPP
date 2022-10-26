#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "Ui thread : " << QThread::currentThread();

    workerThread = new WorkerThread();

    connect(workerThread, &WorkerThread::currentCount, this, &Widget::currentCount);
    connect(workerThread, &WorkerThread::finished, workerThread, &WorkerThread::deleteLater);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_start_pushButton_clicked()
{
    workerThread->start();
}


void Widget::on_pause_pushButton_clicked()
{
    workerThread->pause();
}


void Widget::on_resume_pushButton_clicked()
{
    workerThread->resume();
}

void Widget::currentCount(int value)
{
    ui->progressBar->setValue(value);
}



void Widget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)

    if (workerThread) {
        workerThread->exit();
    }
}
