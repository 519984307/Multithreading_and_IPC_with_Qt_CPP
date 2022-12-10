#include "widget.h"
#include "ui_widget.h"

#include "calculatoradaptor.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    slaveCalculator = new SlaveCalculator(this);
    new CalculatorInterfaceAdaptor(slaveCalculator);
    QDBusConnection connection = QDBusConnection::sessionBus();

    // Here you pass in the Object that you want to pass to DBus. Take note of this information, it is needed for the client.
    connection.registerObject("CalculatorServicePath", slaveCalculator);

    // Here you pass in the service name. Take note of this information, it is needed for the client.
    connection.registerService("com.blikoon.CalculatorService");
}

Widget::~Widget()
{
    delete ui;
}

