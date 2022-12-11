/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -p calculatorinterface slavecalculator.xml
 *
 * qdbusxml2cpp is Copyright (C) 2022 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef CALCULATORINTERFACE_H
#define CALCULATORINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.blikoon.CalculatorInterface
 */
class ComBlikoonCalculatorInterfaceInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.blikoon.CalculatorInterface"; }

public:
    ComBlikoonCalculatorInterfaceInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~ComBlikoonCalculatorInterfaceInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<double> divide(double divident, double divisor)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(divident) << QVariant::fromValue(divisor);
        return asyncCallWithArgumentList(QStringLiteral("divide"), argumentList);
    }

    inline QDBusPendingReply<double> multiply(double factor1, double factor2)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(factor1) << QVariant::fromValue(factor2);
        return asyncCallWithArgumentList(QStringLiteral("multiply"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace com {
  namespace blikoon {
    using CalculatorInterface = ::ComBlikoonCalculatorInterfaceInterface;
  }
}
#endif
