#include "dialog.h"

#include <QFileDialog>
#include <QBuffer>
#include <QtCore/QDebug>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent), sharedMemory("QSharedMemoryExample")
{
    ui.setupUi(this);
    connect(ui.loadFromFileButton, SIGNAL(clicked(bool)), SLOT(loadFromFile()));
    connect(ui.loadFromSharedMemoryButton, SIGNAL(clicked(bool)), SLOT(loadFromMemory()));

    setWindowTitle("SharedMemory Example");
}

void Dialog::loadFromFile()
{
    // 공유메모리 영역에 접근할 수 있는지 확인
    if(sharedMemory.isAttached()) {
        detach();
    }

    ui.label->setText(tr("Select and image file"));

    QString fileName = QFileDialog::getOpenFileName(0, QString(), QString(), tr("Images (*.png *.xpm *.jpg)"));

    QImage image;
    if(!image.load(fileName)) {
        ui.label->setText(tr("Selected file is not an image, please select another."));
        return;
    }
    ui.label->setPixmap(QPixmap::fromImage(image));

    // load into shared memory
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << image;
    int size = buffer.size();

    if(!sharedMemory.create(size)) {
        ui.label->setText(tr("Unable to create shared memroy segment."));
        return;
    }

    sharedMemory.lock();
    char *to = (char*)sharedMemory.data();
    const char *from = buffer.data().data();

    memcpy(to, from, qMin(sharedMemory.size(), size));
    sharedMemory.unlock();

}

void Dialog::loadFromMemory()
{
    if(!sharedMemory.attach()) {
        ui.label->setText(tr("Unable to attach to shared memory segment.\n Load an image first."));
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
    ui.label->setPixmap(QPixmap::fromImage(image));
}

void Dialog::detach()
{
    if(!sharedMemory.detach()) {
        ui.label->setText("Unable to detach form shared memory");
    }
}

Dialog::~Dialog()
{

}
