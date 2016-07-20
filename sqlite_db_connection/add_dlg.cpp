#include <QtGui>

#include "add_dlg.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFont>

add_dlg::add_dlg(QWidget *parent):QDialog(parent)
{
    codec = QTextCodec::codecForName("UTF-8");
    QFont font("unifont", 10, QFont::Bold);
    setFont(font);

    setWindowTitle(codec->toUnicode("등록"));

    init();
    createAction();
}

void add_dlg::init()
{
    lbl_name = new QLabel(codec->toUnicode("이름"));
    lbl_tel = new QLabel(codec->toUnicode("연락처"));
    lbl_address = new QLabel(codec->toUnicode("주소"));

    te_name = new QLineEdit("");
    te_tel = new QLineEdit("");
    te_address = new QLineEdit("");

    formGroupBox = new QGroupBox(codec->toUnicode("주소입력란"));
    QFormLayout *flayout = new QFormLayout;
    flayout->addRow(lbl_name, te_name);
    flayout->addRow(lbl_tel, te_tel);
    flayout->addRow(lbl_address, te_address);

    formGroupBox->setLayout(flayout);

    pbt_add = new QPushButton(codec->toUnicode("등록"));
    vGroupBox = new QGroupBox(tr("Action"));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(pbt_add);

    vGroupBox->setLayout(vlayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(vGroupBox);
    setLayout(mainLayout);
}

void add_dlg::createAction()
{
    connect(pbt_add, SIGNAL(clicked(bool)), this, SLOT(db_insert()));
}

void add_dlg::db_insert()
{
    QString name = te_name->text();
    QString tel = te_tel->text();
    QString address = te_address->text();

    if(name.length() < 1) {
        QMessageBox::warning(this, "Error Message", codec->toUnicode("이름을 입력해 주세요."));
    } else if(tel.length() < 1) {
        QMessageBox::warning(this, "Error Message", codec->toUnicode("연락처를 입력해 주세요."));
    } else if(address.length() < 1) {
         QMessageBox::warning(this, "Error Message", codec->toUnicode("주소를 입력해 주세요."));
    } else {
        QString text = QString("INSERT INTO address(name, tel, address) VALUES ('%1', '%2', '%3')").arg(name).arg(tel).arg(address);

        QSqlQuery query;
        query.exec(codec->fromUnicode(text));

        accept();
    }
}
