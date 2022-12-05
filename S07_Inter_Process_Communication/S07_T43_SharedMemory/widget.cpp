#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QBuffer>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , sharedMemory("SharedMemoryDemoApp")
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_loadImage_pushButton_clicked()
{
    // Detach from the sharedMemory first, then recreate it.
    if (sharedMemory.isAttached()) {
        qDebug() << "Shared Memory is attached, detaching";
        detach();
    }

    ui->image_label->setText(tr("Select an Image File"));
    QString filename = QFileDialog::getOpenFileName(nullptr, QString(), QString(), tr("Images (*.png *.xpm *.jpg)"));
    // QString fileName = QFileDialog::getOpenFileName(nullptr, QString(), QString(), tr("Images (*.png *.xpm *.jpg)"));

    QImage image;
    if (!image.load(filename)) {
        ui->image_label->setText(tr("Selected file is not an image, please select another"));
        return;
    }

    ui->image_label->setPixmap(QPixmap::fromImage(image));

    // Load into shared memory
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << image;
    int size = buffer.size();

    qDebug() << "Shared Memory Size: " << size;

    if (!sharedMemory.create(size)) {
        ui->image_label->setText(tr("Unable to create shared memory segment"));
        qDebug() << sharedMemory.errorString();
        qDebug() << "Is attached : " << sharedMemory.isAttached();
        return;
    }

    sharedMemory.lock();

    char* to = static_cast<char*>(sharedMemory.data());
    const char* from = buffer.data().data();
    memcpy(to, from, qMin(sharedMemory.size(), size));

    sharedMemory.unlock();
}


void Widget::on_loadSharedMemory_pushButton_clicked()
{
    // Try to attach to the shared memory
    if (!sharedMemory.attach()) {
        ui->image_label->setText(tr("Unable to attach to shared memory segment.\n" \
                                    "load in the data first."));
        return;
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    QImage image;

    sharedMemory.lock();

    buffer.setData((char*)sharedMemory.constData(), sharedMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in >> image;

    sharedMemory.unlock();

    sharedMemory.detach();

    ui->image_label->setPixmap(QPixmap::fromImage(image));
}

void Widget::detach()
{
    if (!sharedMemory.detach()) {
        ui->image_label->setText("Cannot detach from the shared memory");
    }
}

