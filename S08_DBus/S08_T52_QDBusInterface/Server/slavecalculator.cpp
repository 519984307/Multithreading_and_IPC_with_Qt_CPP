#include "slavecalculator.h"

#include <QDebug>

SlaveCalculator::SlaveCalculator(QObject *parent)
    : QObject{parent}
{

}

double SlaveCalculator::multiply(double factor1, double factor2)
{
    qDebug() << "Server: multiply method called";

    double product = factor1 * factor2;
    emit productResult(product);
    return product;
}

double SlaveCalculator::divide(double divident, double divisor)
{
    qDebug() << "Server: divide method called";

    double quotient = divident/divisor;
    emit divisionResult(quotient);
    return quotient;
}
