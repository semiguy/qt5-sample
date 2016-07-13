#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QListView>
#include <QListWidget>
#include <QTextCodec>

class Window:public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    QTextCodec *codec;
    QListWidget *listWidget;
};

#endif // WINDOW_H
