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
    QStringList findFiles(const QString &startDir, const QStringList &filters); // Utility function that recursively searches for files.
    QMap<QString, int> singleThreadedWordCount(const QStringList &files); // Single threaded

    // countWords counts the words in a single file. This function is called in parallel by several threads and must be thread safe. This is the map function.
    static QMap<QString, int> countWords(const QString &file);

    // reduce adds the results from map to the final result. This functor will only be called by one thread at a time.
    static void reduce(QMap<QString, int> &results, const QMap<QString, int> &w);

private slots:
    void on_chooseDirectory_pushButton_clicked();

    void on_findFiles_pushButton_clicked();

    void on_singleThreaded_pushButton_clicked();

    void on_mapReduced_pushButton_clicked();

private:
    Ui::Widget *ui;

    QString chosenDir;
    QStringList files;
    QFuture<QMap<QString, int>> future;
};
#endif // WIDGET_H
