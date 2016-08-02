#ifndef CUSTOM_CPU_WIDGET_H
#define CUSTOM_CPU_WIDGET_H

#include <QtWidgets>

class custom_cpu_widget:public QWidget
{
    Q_OBJECT

public:
    custom_cpu_widget(QWidget *parent = 0); // CPU USED 위젯 클래스 생성자
    void cpu_set_widget_level(int level);   // CPU 사용 레벨을 설정할 멤버 함수

private:
    int w_width;    // 위젯의 가로크기 멤버변수
    int w_height;   // 위젯의 세로크기 멤버 변수
    int cpu_used_level; // CPU 사용율을 변수에 저장하기 위한 멤버 변수

protected:
    virtual void paintEvent(QPaintEvent *event);    // CPU 사용율을 그리는 함
};

#endif // CUSTOM_CPU_WIDGET_H
