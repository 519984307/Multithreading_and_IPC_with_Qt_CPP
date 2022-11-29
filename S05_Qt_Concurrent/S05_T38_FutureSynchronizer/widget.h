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
    static void reduce(int & sum, int value);

private slots:
    void on_filterButton_pushButton_clicked();

    void on_filter_spinBox_valueChanged(int arg1);

private:
    Ui::Widget *ui;

    int filterValue;
    QList<int> intList;
    QFuture<int> future;
    QFutureWatcher<int> futureWatcher;
};
#endif // WIDGET_H
