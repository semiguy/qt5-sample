#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "conn_dlg.h"
#include <QAction>
#include <QTreeView>
#include <QTableView>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QSplitter>
#include <QToolBar>

class MainWindow:public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    conn_dlg *conn_dialog;
    void db_conn(QString host, QString user, QString passwd, QString database);
    void create_tree();

private:
    QString host, user, passwd, database;
    QTextCodec *codec;

    QToolBar *ToolBar;
    QAction *ToolBar_connect;
    QAction *ToolBar_close;

    QTreeView *tree;
    QStandardItemModel *treeModel;

    QTableView *table_view;
    QAbstractItemModel *tab_model;
    QItemSelectionModel *tab_selectionModel;

    QTableView *table_view2;
    QAbstractItemModel *tab_model2;
    QItemSelectionModel *tab_selectionModel2;

    QWidget *main_page;

    QSplitter *splitter;

    void init();
    void create_toolbar();
    void create_view();
    void create_action();

private slots:
    void slot_select_tree(const QModelIndex &index);
    void slot_ToolBar_conn();
    void slot_ToolBar_close();
};

#endif // MAINWINDOW_H
