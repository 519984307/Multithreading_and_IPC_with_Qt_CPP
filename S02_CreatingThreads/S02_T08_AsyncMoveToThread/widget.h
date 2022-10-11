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

    void on_stop_pushButton_clicked();

    void on_information_pushButton_clicked();

protected:
    // QWidget interface
    virtual void closeEvent(QCloseEvent *event) override;

private:
    Ui::Widget *ui;

    QThread * thread = nullptr;

};

#endif // WIDGET_H
