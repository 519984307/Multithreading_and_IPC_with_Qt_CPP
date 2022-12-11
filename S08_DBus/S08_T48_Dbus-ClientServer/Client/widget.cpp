#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("DBus Client");

    calcHandle = new com::blikoon::CalculatorInterface("com.blikoon.CalculatorService", "/CalculatorServicePath", QDBusConnection::sessionBus());
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_multiply_pushButton_clicked()
{
    if (calcHandle) {
        double result = calcHandle->multiply(ui->number1_doubleSpinBox->value(), ui->number2_doubleSpinBox->value());
        ui->result_lineEdit->setText(QString::number(result));
    } else {
        ui->result_lineEdit->setText("Result not valid");
    }
}


void Widget::on_divide_pushButto_clicked()
{
    if (calcHandle) {
        double result = calcHandle->divide(ui->number1_doubleSpinBox->value(), ui->number2_doubleSpinBox->value());
        ui->result_lineEdit->setText(QString::number(result));
    } else {
        ui->result_lineEdit->setText("Result not valid");
    }
}

