#include <QtGui>

#include "mywidget.h"

MyWidget::MyWidget()
{
    setFixedSize(500,200);

    static QIcon Img1(QPixmap("./images/menu_recovery.png"));
    static QIcon Img2(QPixmap("./images/menu_setting.png"));
    static QIcon Img3(QPixmap("./images/menu_help.png"));
    static QIcon Img4(QPixmap("./images/menu_info.png"));
    static QIcon Img5(QPixmap("./images/menu_dir_search.png"));
    static QIcon Img6(QPixmap("./images/menu_close.png"));

    toolToolBar = addToolBar(tr("Tools"));
    toolToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tool1 = new QAction(Img1, tr("New"), this);
    tool1->setShortcut(tr("Ctrl+F"));

    tool2 = new QAction(Img2, tr("Set"), this);
    tool2->setShortcut(tr("Ctrl+O"));

    tool3 = new QAction(Img3, tr("Help"), this);
    tool3->setShortcut(tr("Ctrl+H"));

    tool4 = new QAction(Img4, tr("Info"), this);
    tool4->setShortcut(tr("Ctrl+I"));

    toolToolBar->addAction(tool1);
    toolToolBar->addAction(tool2);
    toolToolBar->addAction(tool3);
    toolToolBar->addAction(tool4);

    searchToolBar = addToolBar(tr("Search"));
    searchToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    search1 = new QAction(Img5, tr("Search"), this);
    search1->setShortcut(tr("Ctrl+S"));

    search2 = new QAction(Img6, tr("Lookup"), this);
    search2->setShortcut(tr("Ctrl+L"));

    searchToolBar->addAction(search1);
    searchToolBar->addAction(search2);

    connect(tool1, SIGNAL(toggled(bool)), this, SLOT(ToolBarEvent()));
    connect(tool2, SIGNAL(toggled(bool)), this, SLOT(ToolBarEvent()));
    connect(tool3, SIGNAL(toggled(bool)), this, SLOT(ToolBarEvent()));
    connect(tool4, SIGNAL(toggled(bool)), this, SLOT(ToolBarEvent()));
    connect(search1, SIGNAL(toggled(bool)), this, SLOT(ToolBarEvent()));
    connect(search2, SIGNAL(toggled(bool)), this, SLOT(ToolBarEvent()));
}

void MyWidget::ToolBarEvent()
{
    qDebug("QToolBar Event");
}
