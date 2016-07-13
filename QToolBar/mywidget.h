#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>

class MyWidget:public QMainWindow
{
    Q_OBJECT

public:
    MyWidget();

private:
    QToolBar *toolToolBar;
    QAction *tool1;
    QAction *tool2;
    QAction *tool3;
    QAction *tool4;

    QToolBar *searchToolBar;
    QAction *search1;
    QAction *search2;

private slots:
    void ToolBarEvent();
};

#endif // MYWIDGET_H
