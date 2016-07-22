#include <QtGui>
#include <QtSql>
#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow()
{
    init();
    db_conn();
    create_tree();

    setWindowTitle(tr("MySQL Browser"));
}

void MainWindow::init()
{
    codec = QTextCodec::codecForName("UTF-8");
    QFont font("unifont", 10, QFont::Bold);

    splitter = new QSplitter;
    tree = new QTreeView;
    tree->setHeaderHidden(true);

    treeModel = new QStandardItemModel(this);
    tree->setModel(treeModel);

    connect(tree, SIGNAL(clicked(const QModelIndex)), this, SLOT(slot_select_tree(QModelIndex)));

    tab_model = new QStandardItemModel(this);
    table_view = new QTableView;
    table_view->setModel(tab_model);

    tab_selectionModel = new QItemSelectionModel(tab_model);
    table_view->setSelectionModel(tab_selectionModel);
    table_view->setSelectionBehavior(QAbstractItemView::SelectRows);

    splitter->addWidget(tree);
    splitter->addWidget(table_view);

    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 7);
    setCentralWidget(splitter);

}

void MainWindow::db_conn()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("172.16.2.241");
    db.setUserName("root");
    db.setPassword("0000");
    db.setDatabaseName("qttestdb");

    if(!db.open()) {
        QMessageBox::warning(this, "MySQL Browser", "DB Connection fail.");
    } else {
        qDebug("DB Connection success");
    }
}

void MainWindow::create_tree()
{
    QSqlQuery query;
    query.exec("show tables");

    QStandardItem *item1 = new QStandardItem("DataBase");

    while(query.next()) {
        QString name = query.value(0).toString();

        QStandardItem *item2 = new QStandardItem(name);
        item1->appendRow(item2);
        //qDebug("kk : %d", ++i);
    }

    treeModel->appendRow(item1);
}

void MainWindow::slot_select_tree(const QModelIndex &index)
{
    QString table_name = treeModel->data(index, Qt::DisplayRole).toString();
    QString text = QString("desc %1").arg(table_name);

    int size = tab_model->rowCount();
    if(size > 0) {
        tab_model->removeRows(0, size, QModelIndex());
    }

    size = tab_model->columnCount();
    if(size > 0) {
        tab_model->removeColumns(0, size, QModelIndex());
    }

    QSqlQuery query;
    query.exec(text);

    int hCount = 0;
    while(query.next()) {
        QString name = query.value(0).toString();
        tab_model->insertColumn(hCount, QModelIndex());
        tab_model->setHeaderData(hCount, Qt::Horizontal, name);
        hCount++;
    }

    text = QString("select * from %1").arg(table_name);
    query.exec(text);

    int row=0, i=0;
    QString temp;

    while(query.next()) {
        tab_model->insertRows(row, 1, QModelIndex());

        for(i=0; i < hCount; i++) {
            temp = query.value(i).toString();
            tab_model->setData(tab_model->index(row, i, QModelIndex()), temp);
        }

        row++;
    }
}
