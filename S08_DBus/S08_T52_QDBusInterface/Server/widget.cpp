#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include "calculatoradaptor.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("DBus Server");

    slaveCalculator = new SlaveCalculator(this);
    new CalculatorInterfaceAdaptor(slaveCalculator);
    QDBusConnection connection = QDBusConnection::sessionBus();

    // Here you pass in the Object that you want to pass to DBus. Take note of this information, it is needed for the client.
    connection.registerObject("/CalculatorServicePath", slaveCalculator);

    // Here you pass in the service name. Take note of this information, it is needed for the client.
    connection.registerService("com.blikoon.CalculatorService");

    // QDBusMessage Connection
    QDBusConnection::sessionBus().connect(QString(), QString(), "com.blikoon.CalculatorInterface", "message", this, SLOT(messageSlot(QString)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::messageSlot(QString message)
{
    qDebug() << "Got client message in server process : " << message;
}

