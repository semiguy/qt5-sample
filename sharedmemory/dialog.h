#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSharedMemory>
#include "ui_dialog.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void loadFromFile();
    void loadFromMemory();

private:
    void detach();
    Ui::Dialog ui;
    QSharedMemory sharedMemory;

};

#endif // DIALOG_H
