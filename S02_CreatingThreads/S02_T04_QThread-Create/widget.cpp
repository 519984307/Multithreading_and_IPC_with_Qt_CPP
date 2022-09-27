#include "widget.h"
#include "ui_widget.h"

#include <QDebug>


void counting1(int count) {
    for (int i{0}; i < count; i++) {
        qDebug() << "Counting : " << i << "thread : " << QThread::currentThread();
    }
}

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
    // Example 1 : Blocking the gui thread
    // Computationally intensive operation blocking the gui thread.
    /*
    for(int i{0} ; i < 100000 ; i ++) {
        qDebug() << "Counting method called : " << i
                 << "thread :" << QThread::currentThread() << " id : " << QThread::currentThreadId();
    }
    */

    /*
    // 1. Global Function
    thread = QThread::create(counting1, 10000);
    */

    /*
    // 2. Named Lambda Function
    auto countlambda = [](int count){
        for(int i{0} ; i < count ; i ++){
            qDebug() << "countlambda counting...";
            qDebug() << "Counting : " << i <<
                        " thread :" << QThread::currentThread() << " id : " <<
                        QThread::currentThreadId();
        }
    };

    thread = QThread::create(countlambda, 10000);
    */

    /*
    // 3. Non Named Lambda Function
    thread = QThread::create([](){
        for(int i{0} ; i < 100000 ; i ++){
            qDebug() << "Counting : " << i <<
                        " thread :" << QThread::currentThread() << " id : " <<
                        QThread::currentThreadId();
        }

    });
    */

    // 4. Member Function, call from lambda function
    thread = QThread::create([=]() {
        counting();
    });

    connect(thread, &QThread::finished, thread, [](){
        qDebug() << "Thread has finished";
    });

    connect(thread, &QThread::started, thread, [](){
        qDebug() << "Thread has started";
    });

    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();

    qDebug() << thread->isRunning();

    qDebug() << "Clicked on the start button.";
}

void Widget::counting() {
    for (int i{0}; i < 10000; i++) {
        qDebug() << "Counting method called : " << i
                 << " thread :" << QThread::currentThread()
                 << " id : " << QThread::currentThreadId()
                 << "Thread is running : " << thread->isRunning();
    }
}
