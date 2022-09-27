#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QThread>

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

public:
    void counting();

private:
    Ui::Widget *ui;

    QThread * thread = nullptr;
};
#endif // WIDGET_H
