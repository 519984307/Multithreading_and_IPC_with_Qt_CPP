#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusReply>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("DBus Client");

    interface = new QDBusInterface("com.blikoon.CalculatorService", "/CalculatorServicePath", "com.blikoon.CalculatorInterface");
    interface->setParent(this); // Set a parent for automatic memory management by the Qt Framework

    /*
    connect(interface, SIGNAL(productResult(double)), this, SLOT(gotProduct(double)));
    connect(interface, SIGNAL(divisionResult(double)), this, SLOT(gotQuotient(double)));
    */

    /*
    // Code from prior tutorials
    QDBusConnection::sessionBus().connect(QString(), QString(), "com.blikoon.CalculatorInterface", "productResult", "d", this, SLOT(gotProduct(double)));
    QDBusConnection::sessionBus().connect(QString(), QString(), "com.blikoon.CalculatorInterface", "divisionResult", "d", this, SLOT(gotQuotient(double)));
    */
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
    // ui->result_lineEdit->setText(QString::number(quotient));
}


void Widget::on_multiply_pushButton_clicked()
{
    if (interface->isValid()) {
        qDebug() <<"Interface is valid";
    } else {
        qDebug() << "Interface is not valid, getting out";
        return;
    }

    /*
     * // First Approach : Pass arguments directly, limited to 8 arguments
    QDBusReply<double> reply = interface->call("multiply", ui->number1_doubleSpinBox->value(), ui->number2_doubleSpinBox->value());
    */

    /*
     * // Second Approach : Pass argument as a list using QDBusInterface::callWithArgumentList
    QList<QVariant> args;
    args.append(ui->number1_doubleSpinBox->value());
    args.append(ui->number2_doubleSpinBox->value());

    QDBusReply<double> reply = interface->callWithArgumentList(QDBus::Block, "multiply", args);

    if (reply.isValid()) {
        ui->result_lineEdit->setText(QString::number(reply.value()));
    }
    */

    // Third Approach : Call with a Callback Method
    QList<QVariant> args;
    args.append(ui->number1_doubleSpinBox->value());
    args.append(ui->number2_doubleSpinBox->value());
    interface->callWithCallback("multiply", args, this, SLOT(gotProduct(double)));
}


void Widget::on_divide_pushButto_clicked()
{
    if (interface->isValid()) {
        qDebug() <<"Interface is valid";
    } else {
        qDebug() << "Interface is not valid, getting out";
        return;
    }

     // Third Approach : Call with a Callback Method
    QList<QVariant> args;
    args.append(ui->number1_doubleSpinBox->value());
    args.append(ui->number2_doubleSpinBox->value());
    interface->callWithCallback("divide", args, this, SLOT(gotProduct(double)));
}


void Widget::on_sendSignalToServer_pushButton_clicked()
{
    QDBusMessage message = QDBusMessage::createSignal("/CalculatorServicePath", "com.blikoon.CalculatorInterface", "message");
    message << "Hello there";
    QDBusConnection::sessionBus().send(message);
}

