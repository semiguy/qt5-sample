#include <QtGui>
#include <QtSql>
#include "mainwindow.h"

#include <QFont>
#include <QFormLayout>
#include <QHBoxLayout>

MainWindow::MainWindow()
{
    qDebug("MainWindow::MainWindow()");
    init();
    createAction();
    db_con();

    setWindowTitle(tr("MySQL Database Query"));
}

void MainWindow::init()
{
    qDebug("init()");
    codec = QTextCodec::codecForName("UTF-8");
    QFont font("unifont", 10, QFont::Bold);

    lbl_name = new QLabel("Name");
    lbl_owner = new QLabel("Owner");
    lbl_species = new QLabel("Species");
    lbl_sex = new QLabel("Sex");
    lbl_birth = new QLabel("Birth");
    lbl_death = new QLabel("Death");

    te_name = new QLineEdit("beagle");
    te_owner = new QLineEdit("Gwen");
    te_species = new QLineEdit("dog");
    te_sex = new QLineEdit("m");
    te_birth = new QLineEdit("1982-05-06");
    te_death = new QLineEdit("1995-08-13");

    formGroupBox = new QGroupBox(tr("Pet Information"));
    QFormLayout *flayout = new QFormLayout;
    flayout->addRow(lbl_name, te_name);
    flayout->addRow(lbl_owner, te_owner);
    flayout->addRow(lbl_species, te_species);
    flayout->addRow(lbl_sex, te_sex);
    flayout->addRow(lbl_birth, te_birth);
    flayout->addRow(lbl_death, te_death);
    formGroupBox->setLayout(flayout);

    pbt_insert = new QPushButton("INSERT");
    lbl_result1 = new QLabel("Result : ");
    lbl_result2 = new QLabel("");

    horizontalGroupBox = new QGroupBox(tr("Action"));
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(pbt_insert);
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
    qDebug("createAction()");
    connect(pbt_insert, SIGNAL(clicked(bool)), this, SLOT(db_query()));
}

void MainWindow::db_con()
{
    qDebug("db_con()");
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("172.16.2.241");
    db.setUserName("root");
    db.setPassword("0000");
    db.setDatabaseName("qttestdb");
    db.setPort(3306);

    if(!db.open()) {
        lbl_result2->setText("DB Connection fail");
    } else {
        lbl_result2->setText("DB Connection success");
    }
}

void MainWindow::db_query()
{
    qDebug("db_query()");
    int size = tab_model->rowCount();
    qDebug("tab_model->rowCount() = %d", size);
    tab_model->removeRows(0, size, QModelIndex());


    QSqlQuery query;
    query.prepare("INSERT INTO pet(name, owner, species, sex, birth, death) VALUES (:name, :owner, :species, :sex, :birth, :death)");

    query.bindValue(":name", te_name->text());
    query.bindValue(":owner", te_owner->text());
    query.bindValue(":species", te_species->text());
    query.bindValue(":sex", te_sex->text());
    query.bindValue(":birth", te_birth->text());
    query.bindValue(":death", te_death->text());
    query.exec();


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
        tab_model->setData(tab_model->index(i,0, QModelIndex()), name);
        tab_model->setData(tab_model->index(i,1, QModelIndex()), owner);
        tab_model->setData(tab_model->index(i,2, QModelIndex()), species);
        tab_model->setData(tab_model->index(i,3, QModelIndex()), sex);
        tab_model->setData(tab_model->index(i,4, QModelIndex()), birth);
        tab_model->setData(tab_model->index(i,5, QModelIndex()), death);

        i++;
    }

}
