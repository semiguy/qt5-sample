#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QAction>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QAbstractItemModel>
#include <QTableView>
#include <QTextCodec>
#include <QItemSelectionModel>

class MainWindow:public QDialog
{
    Q_OBJECT
public:
    MainWindow();

private:
    QGroupBox *formGroupBox;
    QGroupBox *horizontalGroupBox;
    QGroupBox *tableGroupBox;

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

    QTextCodec *codec;

    QAbstractItemModel *tab_model;
    QTableView *tableView;
    QItemSelectionModel *tab_selectionModel;

    void init();
    void createAction();
    void db_query();

private slots:
    void db_conn();
};

#endif // MAINWINDOW_H
