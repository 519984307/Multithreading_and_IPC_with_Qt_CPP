#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_process = new QProcess(this);

    connect(m_process, &QProcess::started, [](){
       qDebug() << "Process started";
    });

    connect(m_process, &QProcess::finished, this, &Widget::finished);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_chooseProcess_pushButton_clicked()
{
    processPath = QFileDialog::getOpenFileName(this, tr("Open Application"), "/home", tr("Programs (*.exe)"));

    if (!processPath.isNull()) {
        ui->processPath_lineEdit->setText(processPath);
    }
}


void Widget::on_startProcess_pushButton_clicked()
{
    if (!processPath.isNull()) {
        m_process->start(processPath);
    }
}


void Widget::on_stopProces_pushButton_clicked()
{
    // Tutorial Implementation causes the application started in the process to crash
    // m_process->close();

    // Attempt a clean exit. This seems to work!
    m_process->terminate();
}

void Widget::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Process finished. Process exit code : " << exitCode;
    qDebug() << "Process finished. Process exit status : " << exitStatus;
}

