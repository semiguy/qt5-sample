#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QCalendarWidget *cal = new QCalendarWidget(this);

    cal->setMinimumDate(QDate(2016, 01, 01));
    cal->setMaximumDate(QDate(2016, 12, 31));

    cal->setGridVisible(true);
    cal->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);

    //cal->setSelectionMode(QCalendarWidget::NoSelection);
}

Widget::~Widget()
{

}
