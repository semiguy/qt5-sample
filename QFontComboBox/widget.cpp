#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QFontComboBox *fontcombo[5];

    for(int i=0; i < 5; i++) {
        fontcombo[i] = new QFontComboBox(this);
    }

    // 0x0, 모든폰트
    fontcombo[0]->setFontFilters(QFontComboBox::AllFonts);
    // 0x1, 확대 및 축소와 같은 동적 자동 변환이 가능한 폰트
    fontcombo[1]->setFontFilters(QFontComboBox::ScalableFonts);
    // 0x2, 동적 자동 변환이 제공 되지 않는 폰트
    fontcombo[2]->setFontFilters(QFontComboBox::NonScalableFonts);
    // 0x3, 일정한 문자 넓이 형태를 제공하는 폰트
    fontcombo[3]->setFontFilters(QFontComboBox::MonospacedFonts);
    // 0x4, 넓이와 폭의 균형이 잡힌 폰트
    fontcombo[4]->setFontFilters(QFontComboBox::ProportionalFonts);

    int ypos = 30;
    for(int i=0; i < 5; i++) {
        fontcombo[i]->setGeometry(10, ypos, 200, 30);
        ypos += 40;
    }
    // lbl 추가
    lbl = new QLabel("I love Qt programing", this);
    lbl->setGeometry(10, ypos, 200, 30);

    // 폰트의 인덱스를 리턴하는 시그널 함수 currentIndexChanged(int)
    connect(fontcombo[0], SIGNAL(currentIndexChanged(int)), this, SLOT(changedIndex(int)));
    // 선택한 폰트의 QFont를 리턴하는 시그널 함수 currentFontChanged(QFont)
    connect(fontcombo[0], SIGNAL(currentFontChanged(QFont)), this, SLOT(changedFont(const QFont &)));
}

void Widget::changedIndex(int idx)
{
    qDebug("Font Index : %d", idx);
}

void Widget::changedFont(const QFont &f)
{
    lbl->setFont(f.family());
}

Widget::~Widget()
{

}
