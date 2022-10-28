#include "widget.h"
#include "ui_widget.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "Ui thread : " << QThread::currentThread();

    producer = new Producer(this);
    ui->verticalLayout->addWidget(producer);

    consumer = new Consumer(); // The instance of Consumer will be moved to another thread, therefore it is not given a parent.

    thread = new QThread();

    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, [=]() {
        qDebug() << "Application about to exit : " <<QThread::currentThread();
        QApplication::quit();
    });

    // Set up the queued connection
    connect(producer, &Producer::data, consumer, &Consumer::data);

    consumer->moveToThread(thread);

    thread->start();
}

Widget::~Widget()
{
    delete ui;
}



void Widget::closeEvent(QCloseEvent *event)
{
    // Quit thread before closing the application
    thread->quit();

    event->accept();
}
