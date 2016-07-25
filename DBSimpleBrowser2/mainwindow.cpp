#include <QtGui>
#include <QtSql>

#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>


MainWindow::MainWindow()
{
    init();
    create_toolbar();
    create_view();
    create_action();

    setWindowTitle(tr("MySQL Browser"));
}

void MainWindow::init()
{
    codec = QTextCodec::codecForName("UTF-8");
    QFont font("unifont", 10, QFont::Bold);
}

void MainWindow::create_toolbar()
{
    ToolBar = addToolBar(tr("Tools"));
    ToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ToolBar_connect = new QAction(QIcon(":/images/conn.png"), codec->toUnicode("접속"), this);
    ToolBar_connect->setShortcut(tr("Ctrl+C"));
    ToolBar_connect->setStatusTip(codec->toUnicode("접속"));

    ToolBar_close = new QAction(QIcon(":/images/close.png"), codec->toUnicode("종료"),this);
    ToolBar_close->setShortcut(tr("Ctrl+X"));
    ToolBar_close->setStatusTip(codec->toUnicode("종료"));

    ToolBar->addAction(ToolBar_connect);
    ToolBar->addAction(ToolBar_close);

    ToolBar_connect->setEnabled(true);
    ToolBar_close->setDisabled(true);
}

void MainWindow::create_view()
{
    splitter = new QSplitter;

    tree = new QTreeView;
    tree->setHeaderHidden(true);

    treeModel = new QStandardItemModel(this);
    tree->setModel(treeModel);

    tab_model = new QStandardItemModel(this);
    table_view = new QTableView;
    table_view->setModel(tab_model);

    tab_selectionModel = new QItemSelectionModel(tab_model);
    table_view->setSelectionModel(tab_selectionModel);
    table_view->setSelectionBehavior(QAbstractItemView::SelectRows);

    tab_model2 = new QStandardItemModel(0, 6, this);
    tab_model2->setHeaderData(0, Qt::Horizontal, codec->toUnicode("Field"));
    tab_model2->setHeaderData(1, Qt::Horizontal, codec->toUnicode("Type"));
    tab_model2->setHeaderData(2, Qt::Horizontal, codec->toUnicode("Null"));
    tab_model2->setHeaderData(3, Qt::Horizontal, codec->toUnicode("Key"));
    tab_model2->setHeaderData(4, Qt::Horizontal, codec->toUnicode("Default"));
    tab_model2->setHeaderData(5, Qt::Horizontal, codec->toUnicode("Extra"));

    table_view2 = new QTableView;
    table_view2->setModel(tab_model2);

    tab_selectionModel2 = new QItemSelectionModel(tab_model2);
    table_view2->setSelectionModel(tab_selectionModel2);
    table_view2->setSelectionBehavior(QAbstractItemView::SelectRows);

    main_page = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(main_page);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(table_view);
    mainLayout->addWidget(table_view2);

    splitter->addWidget(tree);
    splitter->addWidget(main_page);

    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 7);
    setCentralWidget(splitter);
}

void MainWindow::db_conn(QString host, QString user, QString passwd, QString database)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(passwd);
    db.setDatabaseName(database);

    if(!db.open()) {
        QMessageBox::warning(this, "MySQL Broswer", "DB Connection Fail.");
    } else {
        qDebug("K DB connection success.");
    }
}

void MainWindow::create_tree()
{
    QSqlQuery query;
    query.exec("show tables");

    QStandardItem *item1 = new QStandardItem("DataBase");

    //int i;
    while(query.next()) {
        QString name = query.value(0).toString();

        QStandardItem *item2 = new QStandardItem(name);
        item1->appendRow(item2);
    }

    treeModel->appendRow(item1);
}

void MainWindow::create_action()
{
    connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_select_tree(QModelIndex)));
    connect(ToolBar_connect, SIGNAL(triggered(bool)), this, SLOT(slot_ToolBar_conn()));
    connect(ToolBar_close, SIGNAL(triggered(bool)), this, SLOT(slot_ToolBar_close()));
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

    text = QString("desc %1").arg(table_name);

    size = tab_model2->rowCount();
    if(size > 0) {
        tab_model2->removeRows(0, size, QModelIndex());
    }

    QSqlQuery query2;
    query2.exec(text);

    i=0;
    while(query2.next()) {
        QString Field = query2.value(0).toString();
        QString Type = query2.value(1).toString();
        QString Null = query2.value(2).toString();
        QString Key = query2.value(3).toString();
        QString Default = query2.value(4).toString();
        QString Extra = query2.value(5).toString();

        tab_model2->insertRows(i, 1, QModelIndex());
        tab_model2->setData(tab_model2->index(i, 0, QModelIndex()), Field);
        tab_model2->setData(tab_model2->index(i, 1, QModelIndex()), Type);
        tab_model2->setData(tab_model2->index(i, 2, QModelIndex()), Null);
        tab_model2->setData(tab_model2->index(i, 3, QModelIndex()), Key);
        tab_model2->setData(tab_model2->index(i, 4, QModelIndex()), Default);
        tab_model2->setData(tab_model2->index(i, 5, QModelIndex()), Extra);

        i++;
    }
}

void MainWindow::slot_ToolBar_conn()
{
    qDebug("slot_ToolBar_conn clicked...");

    conn_dialog = new conn_dlg(this);

    if(conn_dialog->exec() == QDialog::Accepted) {
        if(conn_dialog->db.isOpen()) {
            host = conn_dialog->db.hostName();
            user = conn_dialog->db.userName();
            passwd = conn_dialog->db.password();
            database = conn_dialog->db.databaseName();

            create_tree();

            ToolBar_connect->setDisabled(true);
            ToolBar_close->setEnabled(true);
        }
    } else {
        qDebug("conn_dialog->exec() != QDialog::Accepted");
    }
}

void MainWindow::slot_ToolBar_close()
{
    ToolBar_connect->setEnabled(true);
    ToolBar_close->setDisabled(true);

    conn_dialog->db.close();
}
