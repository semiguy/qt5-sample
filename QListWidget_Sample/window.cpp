#include <QtGui>
#include <QHBoxLayout>
#include <QSize>

#include "window.h"

Window::Window()
{
    codec = QTextCodec::codecForName("UTF-8");
    QFont font("unifont", 10, QFont::Bold);

    listWidget = new QListWidget(this);

    for(int i=0; i < 30; i++) {
        new QListWidgetItem(QString("Item: %1").arg(i), listWidget);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listWidget);
    setLayout(mainLayout);

    resize(450,300);
}
