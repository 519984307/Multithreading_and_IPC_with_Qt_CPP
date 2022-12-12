#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "calculatorinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void gotProduct(double product);
    void gotQuotient(double quotient);

private slots:
    void on_multiply_pushButton_clicked();

    void on_divide_pushButto_clicked();

private:
    Ui::Widget *ui;

    com::blikoon::CalculatorInterface * calcHandle = nullptr;
};
#endif // WIDGET_H
