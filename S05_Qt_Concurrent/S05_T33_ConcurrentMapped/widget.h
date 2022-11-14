#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QFuture>
#include <QFutureWatcher>

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
    void on_modify_pushButton_clicked();

    void on_seeValues_pushButton_clicked();

    static int modify(const int & value);

private:
    Ui::Widget *ui;

    QList<int> list;
    QFuture<int> future;
    QFutureWatcher<int> futureWatcher;

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};
#endif // WIDGET_H
