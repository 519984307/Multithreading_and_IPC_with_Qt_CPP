#include "widget.h"

#include <QApplication>

#include "numberedstring.h"

int main(int argc, char *argv[])
{
    // Register the custom type Numbered String
    qRegisterMetaType<NumberedString>("NumberedString");

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
