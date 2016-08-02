#include "custom_cpu_widget.h"

custom_cpu_widget::custom_cpu_widget(QWidget *parent):QWidget(parent)
{
    this->w_width = 80;
    this->w_height = 100;

    resize(QSize(this->w_width, this->w_height));
    setFixedSize(this->w_width, this->w_height);

    this->cpu_used_level = 10;
}

void custom_cpu_widget::cpu_set_widget_level(int level)
{
    this->cpu_used_level = level;
    // repaint() 함수를 호출 하면 PaintEvent() 멤버함수가 호출된다.
    this->repaint();
}

void custom_cpu_widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setPen(QColor(0, 0, 0));    // 드로잉 외곽선 컬러
    painter.setBrush(QColor(0, 0, 0));  // 드로잉 내부를 채울 컬러
    painter.drawRect(0, 0, this->w_width, this->w_height);  // 사각형을 그림

    int i;
    for(i=21; i >=0; i--) {
        if(this->cpu_used_level > i) {
            painter.setBrush(QColor(153, 255, 0));  // used color
        } else {
            painter.setBrush(QColor(51, 102, 0));   // free color
        }

        painter.drawRect(6, (this->w_height - 8) - (i*4), 30, 3);
        painter.drawRect(43, (this->w_height - 8) - (i*4), 30, 3);
    }
}
