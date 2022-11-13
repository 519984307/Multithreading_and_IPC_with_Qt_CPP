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

public:
    static void modify(int &value);

private slots:
    void on_modify_pushButton_clicked();

    void on_seeValue_pushButton_clicked();

private:
    Ui::Widget *ui;

    QList<int> list;
    QFuture<void> future;
    QFutureWatcher<void> futureWatcher;

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};
#endif // WIDGET_H
