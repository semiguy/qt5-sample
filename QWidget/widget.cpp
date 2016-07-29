#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    edit = new QLineEdit("", this);
    edit->setGeometry(120, 20, 100, 30);
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    //qDebug("Widget::paintEvent...");

    QString img_full_name;

    QPainter painter(this);

    img_full_name = QString("%1/%2").arg(":resources").arg("browser.png");

    QImage image(img_full_name);

    painter.drawPixmap(0, 0,
                       QPixmap::fromImage(image.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    painter.end();
}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    qDebug("[resizeEvent]width:%d, height:%d", this->width(), this->height());
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug("[mousePressEvent]x:%d, y:%d",event->x(), event->y());
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug("[mouseReleaseEvent]x:%d, y:%d",event->x(), event->y());
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug("[mouseDoubleClickEvent]x:%d, y:%d",event->x(), event->y());
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug("[mouseMoveEvent]x:%d, y:%d",event->x(), event->y());
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    qDebug("[keyPressEvent]key: %x", event->key());
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    qDebug("[keyReleaseEvent]key: %x", event->key());

    switch(event->key()) {
    case Qt::Key_A:
        if(event->modifiers()) {
            qDebug("A");
        } else {
            qDebug("a");
        }
    break;

    default:
    break;
    }
}

void Widget::focusInEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    qDebug("[focusInEvent]...");
}


void Widget::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    qDebug("[focusOutEvent]...");
}

Widget::~Widget()
{

}
