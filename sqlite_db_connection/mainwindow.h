#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QAction>
#include <QTableView>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextCodec>
#include <QToolBar>
#include <QWidget>
#include <QComboBox>
#include <QModelIndex>

#define kor(str) QString::fromLocal8Bit(str)

class MainWindow:public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    bool g_DB_Connection;

private:
    QString host, user, passwd, database;
    QTextCodec *codec;

    int selected_num;
    QToolBar *ToolBar;
    QAction *ToolBar_add;
    QAction *ToolBar_close;

    QWidget *main_page;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_modify;
    QPushButton *pushButton_del;

    QTableView *table_view;
    QAbstractItemModel *tab_model;
    QItemSelectionModel *tab_selectionModel;

    void init();
    void create_toolbar();
    void create_action();
    void create_mainWidget();
    void db_connect();
    void db_table_init();

private slots:
    void slot_ToolBar_add();
    void slot_ToolBar_close();
    void slot_pushButton();
    void slot_table_view(const QModelIndex &index);
    void slot_pushButton_modify();
    void slot_pushButton_del();
};

#endif // MAINWINDOW_H
