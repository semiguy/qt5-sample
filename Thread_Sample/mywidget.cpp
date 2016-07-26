#include <QtGui>
#include "mywidget.h"

MyWidget::MyWidget()
{
    pbt_start = new QPushButton("START");
    pbt_pause = new QPushButton("PAUSE");
    pbt_resume = new QPushButton("RESUME");
    pbt_stop = new QPushButton("STOP");

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(pbt_start);
    hLayout->addWidget(pbt_pause);
    hLayout->addWidget(pbt_resume);
    hLayout->addWidget(pbt_stop);

    main_page = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(main_page);
    mainLayout->addLayout(hLayout);

    setCentralWidget(main_page);

    connect(pbt_start, SIGNAL(clicked(bool)), this, SLOT(slot_pbt_start()));
    connect(pbt_pause, SIGNAL(clicked(bool)), this, SLOT(slot_pbt_pause()));
    connect(pbt_resume, SIGNAL(clicked(bool)), this, SLOT(slot_pbt_resume()));
    connect(pbt_stop, SIGNAL(clicked(bool)), this, SLOT(slot_pbt_stop()));
}

void MyWidget::slot_pbt_start() // 시작
{
    my_thread.start();
}

void MyWidget::slot_pbt_pause() // 일시정지
{
    my_thread.pause();
}

void MyWidget::slot_pbt_resume() // 재시작
{
    my_thread.resume();
}

void MyWidget::slot_pbt_stop() // 정지
{
    my_thread.stop();
}
