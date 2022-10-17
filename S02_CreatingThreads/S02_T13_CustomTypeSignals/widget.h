#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QThread>

#include "numberedstring.h"

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
    void on_start_pushButton_clicked();

    void on_information_pushButton_clicked();

    void countDone();
    void currentCount(int value);
    void currentNumberedString(NumberedString ns);
    void threadFinished();

private:
    Ui::Widget *ui;

    QThread * workerThread = nullptr;

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};

#endif // WIDGET_H
