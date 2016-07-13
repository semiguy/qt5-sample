#include <QtGui>

#include "mywidget.h"

MyWidget::MyWidget()
{
    resize(500,200);
    tabWidget1 = new QTabWidget;
    tabWidget1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);

    //tabWidget1->setTabShape(QTabWidget::Triangular);
    tabWidget1->setTabShape(QTabWidget::Rounded);

    search_tab1 = new QWidget;
    search_tab2 = new QWidget;
    search_tab3 = new QWidget;

    static QIcon Img1(QPixmap("./images/menu_dir_search.png"));
    tabWidget1->addTab(search_tab1, Img1, tr("Search"));

    static QIcon Img2(QPixmap("./images/menu_setting.png"));
    tabWidget1->addTab(search_tab2, Img2, tr("Look up"));

    static QIcon Img3(QPixmap("./images/menu_help.png"));
    tabWidget1->addTab(search_tab3, Img3, tr("Data"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget1);
    setLayout(mainLayout);

    setWindowTitle(tr("QTabBar"));
}

void MyWidget::newFile()
{
    qDebug("newFile Menu Action");
}
