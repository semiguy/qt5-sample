#include "widget.h"

#include <QtWidgets>
#include <QBitmap>

Widget::Widget(QWidget *parent)
    //: QWidget(parent)
    :QWidget(0, Qt::FramelessWindowHint), m_embedded(false)
{
    // Qt::FramelessWindowHint : 윈도우의 타이틀바를 표시하지 않게 한다.
    Q_UNUSED(parent);

    qDebug("Widget::Widget(QWidget *parent)");

    update_background(); // 윈도우 모양을 변경

    setWindowTitle(tr("Custom Widget"));

    slider_widget = new custom_slider_widget(this);     // CPU USED 위젯 선언
    slider_widget->slider_set_widget_resize(24, 100);   // CPU USED 위젯 크기
    slider_widget->slider_set_max_value(22);            // 최대 값
    slider_widget->slider_set_min_value(0);             // 최소 값
    slider_widget->slider_set_current_value(12);        // 눈금의 위치의 디폴트 값

    cpu_widget = new custom_cpu_widget(this);           // Slider 위젯 선언
    cpu_widget->cpu_set_widget_level(slider_widget->slider_get_current_value());    // 레벨 디폴트 값

    cpu_widget->setGeometry(40, 100, 80, 100);
    slider_widget->setGeometry(130, 100, 24, 100);

    // Slider 위젯 시그널 이벤트와 슬롯함수 연결
    connect(slider_widget, SIGNAL(valuechanged(int)), this, SLOT(mvaluechanged(int)));
}

void Widget::update_background()
{
    qDebug("Widget::update_background()");
    m_device = QPixmap(":/resources/background.png", "png");
    QBitmap bitmap = m_device.createHeuristicMask();
    setFixedSize(m_device.size());
    setMask(bitmap);
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    //qDebug("Widget::paintEvent(QPaintEvent *event)");
    QPainter painter(this);
    painter.drawPixmap(event->rect(), m_device, event->rect());

    painter.setPen(QColor(116, 116, 118));
    painter.setBrush(QColor(116, 116, 118));
    painter.drawRect(25, 65, 145, 260);
}

void Widget::mvaluechanged(int value)
{
    qDebug("Widget::mvaluechanged,value = %d",value);
    cpu_widget->cpu_set_widget_level(value);
}

Widget::~Widget()
{

}
