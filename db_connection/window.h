#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QAction>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

class MainWindow:public QDialog
{
    Q_OBJECT

public:
    MainWindow();

private:
    QGroupBox *formGroupBox;
    QGroupBox *horizontalGroupBox;

    QLabel *lbl_host;
    QLabel *lbl_user;
    QLabel *lbl_passwd;
    QLabel *lbl_database;
    QLabel *lbl_port;

    QLineEdit *te_host;
    QLineEdit *te_user;
    QLineEdit *te_passwd;
    QLineEdit *te_database;
    QLineEdit *te_port;

    QPushButton *pbt_conn;
    QLabel *lbl_result1;
    QLabel *lbl_result2;

    void init();
    void createAction();

private slots:
    void db_con();

};

#endif // WINDOW_H
