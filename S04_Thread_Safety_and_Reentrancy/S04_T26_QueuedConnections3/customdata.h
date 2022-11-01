#ifndef CUSTOMDATA_H
#define CUSTOMDATA_H

#include <QObject>
#include <QString>


class CustomData
{
public:
    CustomData();
    CustomData(int integerArg, int * pointerArg, const QString &stringArg);

    int m_integer;
    int * m_pointer = nullptr;
    QString m_string;
};

Q_DECLARE_METATYPE(CustomData)

#endif // CUSTOMDATA_H
