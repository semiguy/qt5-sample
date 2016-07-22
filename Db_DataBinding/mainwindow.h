#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QAction>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QTableView>
#include <QTextCodec>
#include <QObject>

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow();

private:
    QGroupBox *formGroupBox;
    QGroupBox *horizontalGroupBox;
    QGroupBox *tableGroupBox;

    QLabel *lbl_name;
    QLabel *lbl_owner;
    QLabel *lbl_species;
    QLabel *lbl_sex;
    QLabel *lbl_birth;
    QLabel *lbl_death;

    QLineEdit *te_name;
    QLineEdit *te_owner;
    QLineEdit *te_species;
    QLineEdit *te_sex;
    QLineEdit *te_birth;
    QLineEdit *te_death;

    QPushButton *pbt_insert;
    QLabel *lbl_result1;
    QLabel *lbl_result2;

    QTextCodec *codec;

    QAbstractItemModel *tab_model;
    QTableView *tableView;
    QItemSelectionModel *tab_selectionModel;

    void init();
    void createAction();
    void db_con();

private slots:
    void db_query();
};

#endif // MAINWINDOW_H
