#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QDir>
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget),
      m_watcher(new QFileSystemWatcher(this))
{
    ui->setupUi(this);

    setWindowTitle("Consumer Process | Files");

    createFileIfNotExists();
    m_watcher->addPath(QString(QDir::tempPath() + "/Qt_S07_T45_SharedFile"));
    connect(m_watcher, &QFileSystemWatcher::fileChanged, this, &Widget::reloadFile);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::reloadFile()
{
    QFile inFile(QString(QDir::tempPath() + "/Qt_S07_T45_SharedFile"));
    QString transferedString;

    if (!inFile.open(QFile::ReadOnly)) {
        qDebug() << "Consumer can't find file : " << inFile.fileName();
        return;
    }

    qDebug() << "Consumer found file : " << inFile.fileName();
    QDataStream in(&inFile);

    ui->textEdit->clear();

    while (!in.atEnd()) {
        in >> transferedString;
        ui->textEdit->setText(transferedString);
    }

    qDebug() << "Consumer done appending data!";
}

void Widget::createFileIfNotExists()
{
    QFile file(QString(QDir::tempPath() + "/Qt_S07_T45_SharedFile"));
    if (!file.exists()) {
        // Just opening the file will create it if it does not exist.
        if (!file.open(QFile::WriteOnly |QIODevice::Append)) {
            qDebug() << "Unable to open the file";
            return;
        }
    }
}

