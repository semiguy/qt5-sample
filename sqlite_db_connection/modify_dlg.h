#ifndef MODIFY_DLG_H
#define MODIFY_DLG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QAction>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QTextCodec>

class modify_dlg : public QDialog
{
    Q_OBJECT

public:
    modify_dlg(QWidget *parent, int num);

private:
    QTextCodec *codec;

    QGroupBox *formGroupBox;
    QGroupBox *vGroupBox;

    QLabel *lbl_name;
    QLabel *lbl_tel;
    QLabel *lbl_address;

    QLineEdit *te_name;
    QLineEdit *te_tel;
    QLineEdit *te_address;

    QPushButton *pbt_modify;

    int modify_num;

    void init(int num);
    void createAction();

private slots:
    void record_modify();
};

#endif // MODIFY_DLG_H
