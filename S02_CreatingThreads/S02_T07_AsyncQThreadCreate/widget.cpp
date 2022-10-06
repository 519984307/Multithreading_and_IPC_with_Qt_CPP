#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QThread>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "Ui thread : " << QThread::currentThread();

    thread = QThread::create([]() {
        QTimer * timer = new QTimer();

        connect(timer, &QTimer::timeout, []() {
            qDebug() << "Timer timed out. Timer running in thread : " << QThread::currentThread();
        });
        timer->start(1000);
    });

    connect(thread, &QThread::started, []() {
        qDebug() << "Thread started : " << QThread::currentThread();
    });

    connect(thread, &QThread::finished, []() {
        qDebug() << "Thread finished : " << QThread::currentThread();
    });

    connect(thread, &QThread::finished, thread, &Widget::deleteLater);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_start_pushButton_clicked()
{
    thread->start();
}

