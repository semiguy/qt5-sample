#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSizeGrip>
#include <QBoxLayout>
#include <QTextEdit>
#include <QSplitter>
#include <QSize>

class SubWindow : public QWidget
{
    Q_OBJECT

public:
    SubWindow(QWidget *parent = 0): QWidget(parent, Qt::SubWindow)
    {
        QSizeGrip *sizegrip = new QSizeGrip(this);
        sizegrip->setFixedSize(sizegrip->sizeHint());

        // SubWindow의 레이아웃 선언
        this->setLayout(new QVBoxLayout);
        this->layout()->setMargin(0); // 여백 설정
        layout()->addWidget(new QTextEdit);

        sizegrip->setWindowFlags(Qt::WindowStaysOnTopHint);
        sizegrip->raise();
    }

    QSize sizeHint() const
    {
        return QSize(200, 100);
    }
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
