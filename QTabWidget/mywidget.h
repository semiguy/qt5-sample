#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QDialog>
#include <QTabWidget>
#include <QMenu>
#include <QHBoxLayout>

class MyWidget:public QWidget
{
    Q_OBJECT

public:
    MyWidget();

private:
    QTabWidget *tabWidget1;
    QWidget *search_tab1;
    QWidget *search_tab2;
    QWidget *search_tab3;

private slots:
    void newFile();
};

#endif // MYWIDGET_H
