#ifndef NUMBEREDSTRING_H
#define NUMBEREDSTRING_H

#include <QMetaType>
#include <QString>

class NumberedString
{
public:
    NumberedString(int number, QString string);

    int number() const;
    const QString &string() const;

private:
    int m_number;
    QString m_string;
};

Q_DECLARE_METATYPE(NumberedString)

#endif // NUMBEREDSTRING_H
