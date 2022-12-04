#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_chooseProcess_pushButton_clicked();

    void on_startProcess_pushButton_clicked();

    void on_stopProces_pushButton_clicked();

    void finished(int exitCode, QProcess::ExitStatus exitStatus = QProcess::NormalExit);

private:
    Ui::Widget *ui;

    QString processPath = nullptr;
    QProcess* m_process;
};
#endif // WIDGET_H
