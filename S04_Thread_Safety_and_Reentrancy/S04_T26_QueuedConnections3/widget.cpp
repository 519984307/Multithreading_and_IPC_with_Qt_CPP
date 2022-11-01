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

    thread = new QThread(this);

    connect(producer, &Producer::data, consumer, &Consumer::data);
    connect(thread, &QThread::started, producer, &Producer::startProduction);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater); // Uncommenting this causes the application to hang on exit, let the framework delete it.

    // Although this is not included in the tutorial implementation I believe it is required to prevent the appliation from crashing on exit.
    connect(thread,&QThread::finished,this, &QApplication::quit);

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
