#include "numberedstring.h"

NumberedString::NumberedString(int number, QString string) : m_number(number), m_string(string)
{

}

int NumberedString::number() const
{
    return m_number;
}

const QString &NumberedString::string() const
{
    return m_string;
}
