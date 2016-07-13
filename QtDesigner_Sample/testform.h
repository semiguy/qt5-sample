#ifndef TESTFORM_H
#define TESTFORM_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "ui_designer_file.h"

class TestForm : public QDialog, private Ui::TestForm
{
    Q_OBJECT

private:
    int total_value;
    int avg_value;

public:
    TestForm(QWidget *parent = 0);

protected slots:
    void sum();
    void avg();
};

#endif // TESTFORM_H
