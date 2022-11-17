#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QtConcurrent>
#include <QThread>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "ui thread : " << QThread::currentThread();
}

Widget::~Widget()
{
    delete ui;
}

QStringList Widget::findFiles(const QString &startDir, const QStringList &filters)
{
    QStringList names;
    QDir dir(startDir);

    const auto files = dir.entryList(filters, QDir::Files);
    for (QString file: files) {
        names += startDir + '/' + file;
    }

    const auto subdirs = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for (const QString &subdir: subdirs) {
        names += findFiles(startDir + '/' + subdir, filters);
    }

    return names;
}

QMap<QString, int> Widget::singleThreadedWordCount(const QStringList &files)
{
    QMap<QString, int> wordCount;
    for (const QString &file: files) {
        QFile f(file);
        f.open(QIODevice::ReadOnly);
        QTextStream textStream(&f);
        while (!textStream.atEnd()) {
            const auto words = textStream.readLine().split(' ');
            for (const QString &word: words) {
                wordCount[word] += 1;
            }
        }
    }
    return wordCount;
}

QMap<QString, int> Widget::countWords(const QString &file)
{
    qDebug() << "countWords method running in thread : " << QThread::currentThread();
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    QTextStream textStream(&f);
    QMap<QString, int> wordCount;

    while (!textStream.atEnd()) {
        const auto words = textStream.readLine().split(' ');
        for (const QString &word: words) {
            wordCount[word] += 1;
        }
    }
    return wordCount;
}

void Widget::reduce(QMap<QString, int> &result, const QMap<QString, int> &w)
{
    QMapIterator<QString, int> i(w);
    while (i.hasNext()) {
        i.next();
        result[i.key()] += i.value();
    }
}


void Widget::on_chooseDirectory_pushButton_clicked()
{
    chosenDir = QFileDialog::getExistingDirectory(this, tr("Open Directory", "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));

    if (!chosenDir.isNull()) {
        qDebug() << "Chosen Directory : " << chosenDir;
        ui->directory_lineEdit->setText(chosenDir);
    } else {
        qDebug() << "Didn't choose any file";
    }
}


void Widget::on_findFiles_pushButton_clicked()
{
    if (!chosenDir.isNull()) {
        ui->foundFiles_label->setText("Finding files...");
        files = findFiles(chosenDir, QStringList() << "*.h" << "*.cpp");
        int fileCount = files.count();
        ui->foundFiles_label->setText("Found : " + QString::number(fileCount) + " files");
    } else {
        qDebug() << "No valid dir selected";
    }
}


void Widget::on_singleThreaded_pushButton_clicked()
{
    if (!files.isEmpty()) {
        QTime startTime = QTime::currentTime();
        QMap<QString, int> wordCount = singleThreadedWordCount(files);
        int timeElapsedMilliseconds = startTime.msecsTo(QTime::currentTime());
        QString message = " Single threaded \n Word count : " +
                QString::number(wordCount.keys().count()) + " \n Time elasped (ms) : " + QString::number(timeElapsedMilliseconds);
        ui->singleThreaded_label->setText(message);
    }
}


void Widget::on_mapReduced_pushButton_clicked()
{
    QTime startTime = QTime::currentTime();

    QFuture future = QtConcurrent::mappedReduced(files, countWords, reduce);
    future.waitForFinished();

    int timeElapsedMilliseconds = startTime.msecsTo(QTime::currentTime());

    QMap<QString, int> total = future.result();
    QString message = " Map Reduced \n Word count : " + QString::number(total.keys().count()) + " \n Time ellapsed : " + QString::number(timeElapsedMilliseconds);
    ui->mapReduced_label->setText(message);
}

