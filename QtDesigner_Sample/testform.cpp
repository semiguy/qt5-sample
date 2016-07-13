#include <QtGui>
#include <QObject>
#include <QString>

#include "testform.h"

TestForm::TestForm(QWidget *parent):QDialog(parent)
{
    setupUi(this);

    connect(total_pbt, SIGNAL(clicked(bool)), this, SLOT(sum()));
    connect(avg_pbt, SIGNAL(clicked(bool)), this, SLOT(avg()));
}

void TestForm::sum()
{
    total_value = 0;
    total_value += kor_let->text().toInt();
    total_value += eng_let->text().toInt();
    total_value += math_let->text().toInt();

    total_let->setText(QString("%1").arg(total_value));
}

void TestForm::avg()
{
    sum();

    avg_value = total_value / 3;
    avg_let->setText(QString("%1").arg(avg_value));
}
