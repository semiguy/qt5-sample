#ifndef CONN_DLG_H
#define CONN_DLG_H

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
#include <QTextCodec>
#include <QWidget>

class conn_dlg : public QDialog
{
    Q_OBJECT
public:
    QSqlDatabase db;
    conn_dlg(QWidget *parent);

private:
    QTextCodec *codec;

    QGroupBox *formGroupBox;
    QGroupBox *vGroupBox;

    QLabel *lbl_host;
    QLabel *lbl_user;
    QLabel *lbl_passwd;
    QLabel *lbl_database;

    QLineEdit *te_host;
    QLineEdit *te_user;
    QLineEdit *te_passwd;
    QLineEdit *te_database;

    QPushButton *pbt_conn;
    QLabel *lbl_result1;
    QLabel *lbl_result2;

    void init();
    void createAction();

private slots:
    void db_conn();
};

#endif // CONN_DLG_H
