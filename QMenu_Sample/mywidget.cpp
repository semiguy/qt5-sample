#include <QtGui>


#include "mywidget.h"

MyWidget::MyWidget()
{
    setFixedSize(500,200);

    static QIcon Img(QPixmap("./image/icon.png"));
    fileMenu = menuBar()->addMenu(tr("&File"));

    newAct = new QAction(Img, tr("&New"), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    exitAct = new QAction(tr("E&xit"),this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(close()));

    fileMenu->addAction(newAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    statusBar()->showMessage(tr("A context menu is available by right-clicking"));
    setWindowTitle(tr("Menus"));
}

void MyWidget::newFile()
{
    qDebug("newFile Menu Action");
}

void MyWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(newAct);
    menu.exec(event->globalPos());
}
