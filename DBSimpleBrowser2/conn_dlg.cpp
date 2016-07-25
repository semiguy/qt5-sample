#include <QtGui>

#include "conn_dlg.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QWidget>

conn_dlg::conn_dlg(QWidget *parent):QDialog(parent)
{
    codec = QTextCodec::codecForName("UTF-8");
    QFont font("unifont", 10, QFont::Bold);
    setFont(font);

    setWindowTitle(tr("Connection"));

    init();
    createAction();
}

void conn_dlg::init()
{
    lbl_host = new QLabel("Host");
    lbl_user = new QLabel("User");
    lbl_passwd = new QLabel("Password");
    lbl_database = new QLabel("Database");

    te_host = new QLineEdit("172.16.2.241");
    te_user = new QLineEdit("root");
    te_passwd = new QLineEdit("0000");
    te_database = new QLineEdit("qttestdb");

    formGroupBox = new QGroupBox(tr("Connection Information"));
    QFormLayout *flayout = new QFormLayout;
    flayout->addRow(lbl_host, te_host);
    flayout->addRow(lbl_user, te_user);
    flayout->addRow(lbl_passwd, te_passwd);
    flayout->addRow(lbl_database, te_database);
    formGroupBox->setLayout(flayout);

    pbt_conn = new QPushButton("DB Connection");
    lbl_result1 = new QLabel("Result : ");
    lbl_result2 = new QLabel("");

    vGroupBox = new QGroupBox(tr("Action"));
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(pbt_conn);
    vlayout->addWidget(lbl_result1);
    vlayout->addWidget(lbl_result2);
    vGroupBox->setLayout(vlayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(vGroupBox);
    setLayout(mainLayout);
}

void conn_dlg::createAction()
{
    connect(pbt_conn, SIGNAL(clicked(bool)), this, SLOT(db_conn()));
}

void conn_dlg::db_conn()
{
    QString host = te_host->text();
    QString user = te_user->text();
    QString passwd = te_passwd->text();
    QString database = te_database->text();

    qDebug() << "conn_dlg::db_conn()" << host << user << passwd << database;

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(passwd);
    db.setDatabaseName(database);

    if(!db.open()) {
        lbl_result2->setText("DB connection fail.");
    } else {
        qDebug("DB Connetion Success!!");
        accept();
    }
}
