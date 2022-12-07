#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QDataStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("File Producer");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_lineEdit_textChanged(const QString &text)
{
    QFile outFile(QString(QDir::tempPath() + "/Qt_S07_T45_SharedFile"));
    qDebug() << "File Path : " << outFile.fileName();
    if (!outFile.open(QFile::ReadOnly | QIODevice::Append)) {
        qDebug() << "Unable to open the file : " << outFile.fileName();
        return;
    }

    QDataStream out(&outFile);
    out << text;
}

