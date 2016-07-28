#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(500,300);
    QToolBar *toolbar = new QToolBar(this);

    QAction *act[5];
    act[0] = new QAction(QIcon(":resources/browser.png"), "Browser", this);
    act[1] = new QAction(QIcon(":resources/calendar.png"), "calendar", this);
    act[2] = new QAction(QIcon(":resources/chat.png"), "chat", this);
    act[3] = new QAction(QIcon(":resources/editor.png"), "editor", this);
    act[4] = new QAction(QIcon(":resources/mail.png"), "mail", this);

    act[0]->setShortcut(Qt::Key_Control | Qt::Key_E);
    act[0]->setToolTip("This is a ToolTip");

    /*
     * setToolButtonStyle
     * Qt::ToolButtonIconOnly, 0, 아이콘만 표시
     * Qt::ToolButtonTextOnly, 1, 버튼명만 표시
     * Qt::ToolButtonTextBesideIcon, 2, 아이콘을 텍스트 안쪽에 표시
     * Qt::ToolButtonTextUnderIcon, 3, 아이콘을 텍스트 아래에 표시
     */
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    for(int i=0; i < 5; i++) {
        toolbar->addAction(act[i]);
    }

    connect(act[0], SIGNAL(triggered(bool)), this, SLOT(trigger1()));
    connect(act[1], SIGNAL(triggered(bool)), this, SLOT(trigger2()));
    connect(act[2], SIGNAL(triggered(bool)), this, SLOT(trigger3()));
    connect(act[3], SIGNAL(triggered(bool)), this, SLOT(trigger4()));
    connect(act[4], SIGNAL(triggered(bool)), this, SLOT(trigger5()));
}

void Widget::trigger1()
{
    qDebug("Tool Button 1 click.");
}

void Widget::trigger2()
{
    qDebug("Tool Button 2 click.");
}

void Widget::trigger3()
{
    qDebug("Tool Button 3 click.");
}

void Widget::trigger4()
{
    qDebug("Tool Button 4 click.");
}

void Widget::trigger5()
{
    qDebug("Tool Button 5 click.");
}

Widget::~Widget()
{

}
