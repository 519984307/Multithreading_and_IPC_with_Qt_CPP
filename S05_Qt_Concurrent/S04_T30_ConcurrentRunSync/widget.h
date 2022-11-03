#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QFuture>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    static void heavyWork();

private slots:
    void on_start_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_pause_pushButton_clicked();

    void on_resume_pushButton_clicked();

private:
    Ui::Widget *ui;

    QFuture<void> future;
};
#endif // WIDGET_H
