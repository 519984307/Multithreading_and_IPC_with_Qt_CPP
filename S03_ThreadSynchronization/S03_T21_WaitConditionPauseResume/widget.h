#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "workerthread.h"

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

    void on_pause_pushButton_clicked();

    void on_resume_pushButton_clicked();

    void currentCount(int value);

private:
    Ui::Widget *ui;

    WorkerThread * workerThread = nullptr;

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};
#endif // WIDGET_H
