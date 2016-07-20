#include <QtGui>

#include "modify_dlg.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QByteArray>
#include <QMessageBox>

modify_dlg::modify_dlg(QWidget *parent, int num):QDialog(parent)
{
    codec = QTextCodec::codecForName("UTF-8");

    QFont font("unifont", 10, QFont::Bold);
    setFont(font);

    setWindowTitle(codec->toUnicode("수정"));

    init(num);
    createAction();
}

void modify_dlg::init(int num)
{
    lbl_name = new QLabel(codec->toUnicode("이름"));
    lbl_tel = new QLabel(codec->toUnicode("연락처"));
    lbl_address = new QLabel(codec->toUnicode("주소"));

    te_name = new QLineEdit("");
    te_tel = new QLineEdit("");
    te_address = new QLineEdit("");

    formGroupBox = new QGroupBox(codec->toUnicode("주소 입력란"));
    QFormLayout *flayout = new QFormLayout;
    flayout->addRow(lbl_name, te_name);
    flayout->addRow(lbl_tel, te_tel);
    flayout->addRow(lbl_address, te_address);

    formGroupBox->setLayout(flayout);

    pbt_modify = new QPushButton(codec->toUnicode("수정"));
    vGroupBox = new QGroupBox(tr("Action"));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(pbt_modify);
    vGroupBox->setLayout(vlayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(vGroupBox);
    setLayout(mainLayout);

    QString text = QString("SELECT * FROM address WHERE num=%1").arg(num);

    qDebug("num : %d", num);

    QSqlQuery query;
    query.exec(codec->fromUnicode(text));

    query.next();

    QByteArray fnum = query.value(0).toByteArray();
    QByteArray fname = query.value(1).toByteArray();
    QByteArray ftel = query.value(2).toByteArray();
    QByteArray faddress = query.value(3).toByteArray();

    te_name->setText(codec->toUnicode(fname));
    te_tel->setText(codec->toUnicode(ftel));
    te_address->setText(codec->toUnicode(faddress));

    modify_num = num;
}

void modify_dlg::createAction()
{
    connect(pbt_modify, SIGNAL(clicked(bool)), this, SLOT(record_modify()));
}

void modify_dlg::record_modify()
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
        QString text;
        text = QString("UPDATE address SET name='%1', tel='%2', address='%3' WHERE num='%4'").arg(name).arg(tel).arg(address).arg(modify_num);

        QSqlQuery query;
        query.exec(codec->fromUnicode(text));

        accept();
    }
}
