#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    dataSource << 1 << 2 << 34 << 55 << 4 << 11 << 22 << 34 << 55
                   << 4 << 1 << 2 << 34 << 55 << 4 << 1 << 2 << 34 << 55 << 4 << 2222;
    atEnd = false;

    freeSpace = new QSemaphore(BUFFER_SIZE);
    availableSpace = new QSemaphore(0);

    producer = new Producer(dataSource, bufferArray, BUFFER_SIZE, freeSpace, availableSpace, &atEnd);
    consumer = new Consumer(bufferArray, BUFFER_SIZE, freeSpace, availableSpace, &atEnd);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_start_pushButton_clicked()
{
    producer->start();
    consumer->start();

    producer->wait();
    consumer->wait();

    atEnd = false; // Allows the app to start producing again if the button is pressed a second time.
}

