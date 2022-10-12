#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QThreadPool>

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


void Widget::on_start_pushButton_clicked()
{
    Worker * worker = new Worker();

    // If the auto-deletion flag is set to true then Qt manages the memory, otherwise the memory allocated to the instance of Worker needs to be release.
    // worker->setAutoDelete(false);

    QThreadPool::globalInstance()->start(worker);
}


void Widget::on_information_pushButton_clicked()
{

}

