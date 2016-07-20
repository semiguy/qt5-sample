#include <QtGui>
#include <QtSql>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QObject>
#include <QString>

#include "window.h"

MainWindow::MainWindow()
{
    qDebug() << QSqlDatabase::drivers();
    init();
    createAction();
    //setFixedSize(500,400);
    setWindowTitle(tr("MySQL Database Connection"));

}

void MainWindow::init()
{
    lbl_host = new QLabel("Host");
    lbl_user = new QLabel("User");
    lbl_passwd = new QLabel("Password");
    lbl_database = new QLabel("DataBase");
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

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(horizontalGroupBox);
    setLayout(mainLayout);
}

void MainWindow::createAction()
{
    connect(pbt_conn, SIGNAL(clicked(bool)), this, SLOT(db_con()));
}

void MainWindow::db_con()
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
        qDebug("Db Connection Fail.");
        lbl_result2->setText("DB Connection Fail");
    } else {
        qDebug("DB Connection success.");
        lbl_result2->setText("DB Connection success");
    }
}
