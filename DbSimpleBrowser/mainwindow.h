#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QAction>
#include <QTreeView>
#include <QTableView>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QSplitter>
#include <QTextCodec>

class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    QTextCodec *codec;

    QTreeView *tree;
    QStandardItemModel *treeModel;

    QTableView *table_view;
    QAbstractItemModel *tab_model;
    QItemSelectionModel *tab_selectionModel;
    QSplitter *splitter;

    void init();
    void db_conn();
    void create_tree();

private slots:
    void slot_select_tree(const QModelIndex &index);
};

#endif // MAINWINDOW_H
