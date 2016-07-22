#include <QtGui>
#include <QtSql>
#include "mainwindow.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAbstractItemView>

MainWindow::MainWindow()
{
    init();
    createAction();
    setWindowTitle(tr("MySQL Database Connection"));
}

void MainWindow::init()
{
    codec = QTextCodec::codecForName("UTF-8");
    QFont font("unifont", 10, QFont::Bold);

    lbl_host = new QLabel("Host");
    lbl_user = new QLabel("User");
    lbl_passwd = new QLabel("Password");
    lbl_database = new QLabel("Database");
    lbl_port = new QLabel("Port");

    te_host = new QLineEdit("172.16.2.241");
    te_user = new QLineEdit("root");
    te_passwd = new QLineEdit("0000");
    te_database = new QLineEdit("qttestdb");
    te_port = new QLineEdit("3306");

    formGroupBox = new QGroupBox(tr("Connection Information"));
    QFormLayout *flayout = new QFormLayout;
    flayout->addRow(lbl_host, te_host);
    flayout->addRow(lbl_user, te_user);
    flayout->addRow(lbl_passwd, te_passwd);
    flayout->addRow(lbl_database, te_database);
    flayout->addRow(lbl_port, te_port);

    formGroupBox->setLayout(flayout);

    pbt_conn = new QPushButton("DB Connection");
    lbl_result1 = new QLabel("Result : ");
    lbl_result2 = new QLabel("");

    horizontalGroupBox = new QGroupBox(tr("Action"));
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(pbt_conn);
    hlayout->addWidget(lbl_result1);
    hlayout->addWidget(lbl_result2);
    horizontalGroupBox->setLayout(hlayout);

    tab_model = new QStandardItemModel(0, 6, this);
    tableView = new QTableView;
    tableView->setModel(tab_model);

    tab_model->setHeaderData(0, Qt::Horizontal, codec->toUnicode("name"));
    tab_model->setHeaderData(1, Qt::Horizontal, codec->toUnicode("owner"));
    tab_model->setHeaderData(2, Qt::Horizontal, codec->toUnicode("species"));
    tab_model->setHeaderData(3, Qt::Horizontal, codec->toUnicode("sex"));
    tab_model->setHeaderData(4, Qt::Horizontal, codec->toUnicode("birth"));
    tab_model->setHeaderData(5, Qt::Horizontal, codec->toUnicode("death"));

    tab_selectionModel = new QItemSelectionModel(tab_model);
    tableView->setSelectionModel(tab_selectionModel);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(tableView);
    setLayout(mainLayout);

    resize(500,400);
}

void MainWindow::createAction()
{
    connect(pbt_conn, SIGNAL(clicked(bool)), this, SLOT(db_conn()));
}

void MainWindow::db_conn()
{
    QString host = te_host->text();
    QString user = te_user->text();
    QString passwd = te_passwd->text();
    QString database = te_database->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(passwd);
    db.setDatabaseName(database);
    db.setPort(3306);

    if(!db.open()) {
        lbl_result2->setText("DB Connection fail");
    } else {
        lbl_result2->setText("DB Connection success");
        db_query();
    }
}

void MainWindow::db_query()
{
    QSqlQuery query;
    query.exec("select * from pet");

    int i=0;

    while(query.next()) {
        QString name = query.value(0).toString();
        QString owner = query.value(1).toString();
        QString species = query.value(2).toString();
        QString sex = query.value(3).toString();
        QString birth = query.value(4).toString();
        QString death = query.value(5).toString();

        qDebug() << name;

        tab_model->insertRows(i, 1, QModelIndex());
        tab_model->setData(tab_model->index(i, 0, QModelIndex()), name);
        tab_model->setData(tab_model->index(i, 1, QModelIndex()), owner);
        tab_model->setData(tab_model->index(i, 2, QModelIndex()), species);
        tab_model->setData(tab_model->index(i, 3, QModelIndex()), sex);
        tab_model->setData(tab_model->index(i, 4, QModelIndex()), birth);
        tab_model->setData(tab_model->index(i, 5, QModelIndex()), death);
    }
    i++;
}
