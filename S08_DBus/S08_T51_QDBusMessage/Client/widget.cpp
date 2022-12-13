#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("DBus Client");

    QDBusConnection::sessionBus().connect(QString(), QString(), "com.blikoon.CalculatorInterface", "productResult", "d", this, SLOT(gotProduct(double)));
    QDBusConnection::sessionBus().connect(QString(), QString(), "com.blikoon.CalculatorInterface", "divisionResult", "d", this, SLOT(gotQuotient(double)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::gotProduct(double product)
{
    qDebug() << "Product from Server process : " << product;
    ui->result_lineEdit->setText(QString::number(product));
}

void Widget::gotQuotient(double quotient)
{
    qDebug() << "Product from Server process : " << quotient;
    ui->result_lineEdit->setText(QString::number(quotient));
}


void Widget::on_multiply_pushButton_clicked()
{
    // 1st Example : Sending a message without returning a response using the QDbusConnection::call method
    QDBusMessage m = QDBusMessage::createMethodCall("com.blikoon.CalculatorService",
                                                        "/CalculatorServicePath",
                                                        "com.blikoon.CalculatorInterface",
                                                        "multiply");

    m << ui->number1_doubleSpinBox->value() << ui->number2_doubleSpinBox->value();
    bool queued = QDBusConnection::sessionBus().send(m);

    qDebug() << "Message queued : " << queued;


    // 2nd Example : Sending a message returning a response
    QDBusMessage response = QDBusConnection::sessionBus().call(m);
    qDebug() << "Response from the server : " << response.arguments();

    if (response.type() == QDBusMessage::ReplyMessage) {
        ui->result_lineEdit->setText(QString::number(response.arguments()[0].toDouble()));
    }
}


void Widget::on_divide_pushButto_clicked()
{
    // 1st Example : Sending a message without returning a response using the QDbusConnection::call method
    QDBusMessage m = QDBusMessage::createMethodCall("com.blikoon.CalculatorService",
                                                        "/CalculatorServicePath",
                                                        "com.blikoon.CalculatorInterface",
                                                        "divide");

    m << ui->number1_doubleSpinBox->value() << ui->number2_doubleSpinBox->value();
    bool queued = QDBusConnection::sessionBus().send(m);

    qDebug() << "Message queued : " << queued;


    // 2nd Example : Sending a message returning a response
    QDBusMessage response = QDBusConnection::sessionBus().call(m);
    qDebug() << "Response from the server : " << response.arguments();

    if (response.type() == QDBusMessage::ReplyMessage) {
        ui->result_lineEdit->setText(QString::number(response.arguments()[0].toDouble()));
    }
}


void Widget::on_sendSignalToServer_pushButton_clicked()
{
    QDBusMessage message = QDBusMessage::createSignal("/CalculatorServicePath", "com.blikoon.CalculatorInterface", "message");
    message << "Hello there";
    QDBusConnection::sessionBus().send(message);
}

