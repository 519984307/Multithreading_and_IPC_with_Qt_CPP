#include "widget.h"
#include "ui_widget.h"

#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "Main Thread: " << QThread::currentThread();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_start_pushButton_clicked()
{
    // Computationally intensive operation blocking the gui thread.
    for(int i{0} ; i < 100000 ; i ++) {
        qDebug() << "Counting method called : " << i
                 << "thread :" << QThread::currentThread() << " id : " << QThread::currentThreadId();
    }

    qDebug() << "Clicked on the start button.";
}

