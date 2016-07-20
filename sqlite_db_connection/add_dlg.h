#ifndef ADD_DLG_H
#define ADD_DLG_H

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

class add_dlg : public QDialog
{
    Q_OBJECT

public:
    add_dlg(QWidget *parent);

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

    QPushButton *pbt_add;

    void init();
    void createAction();

private slots:
    void db_insert();
};

#endif // ADD_DLG_H
