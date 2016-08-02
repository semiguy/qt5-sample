#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

#include "custom_cpu_widget.h"
#include "custom_slider_widget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    // Slider 시그널 이벤트와 연결할 슬롯 함수
    void mvaluechanged(int value);

private:
    // CPU USED 위젯
    custom_cpu_widget *cpu_widget;
    // Slider 위젯 선언
    custom_slider_widget *slider_widget;

    bool m_embedded;
    // 윈도우 영역을 MASK할 백그라운드 이미지 리소스
    QPixmap m_device;

protected:
    // 윈도우 모양을 변경
    void update_background();
    virtual void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H
