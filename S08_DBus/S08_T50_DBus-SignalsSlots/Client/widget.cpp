#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("DBus Client");

    calcHandle = new com::blikoon::CalculatorInterface("com.blikoon.CalculatorService", "/CalculatorServicePath", QDBusConnection::sessionBus());

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
    if (calcHandle) {
        double result = calcHandle->multiply(ui->number1_doubleSpinBox->value(), ui->number2_doubleSpinBox->value());
        // ui->result_lineEdit->setText(QString::number(result));
    } else {
        ui->result_lineEdit->setText("Result not valid");
    }
}


void Widget::on_divide_pushButto_clicked()
{
    if (calcHandle) {
        double result = calcHandle->divide(ui->number1_doubleSpinBox->value(), ui->number2_doubleSpinBox->value());
        // ui->result_lineEdit->setText(QString::number(result));
    } else {
        ui->result_lineEdit->setText("Result not valid");
    }
}

