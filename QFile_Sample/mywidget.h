#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QLabel>
#include <QMenu>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QObject>

class MyWidget:public QMainWindow
{
    Q_OBJECT

public:
    MyWidget();

private:
    QMenu *fileMenu;
    QAction *openAct;
    QHBoxLayout *layout;
    QTextEdit *edit;
    QString fileName;

private slots:
    void openFile();
};

#endif // MYWIDGET_H
