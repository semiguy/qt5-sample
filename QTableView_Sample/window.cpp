#include <QtGui>
#include <QVBoxLayout>
#include <QMessageBox>

#include "window.h"

Window::Window()
{
    codec = QTextCodec::codecForName("UTF-8"); //eucKR
    QFont font("gulim", 10);

    tab_model = new QStandardItemModel(0, 4, this);
    tableView = new QTableView;
    tableView->setModel(tab_model);

    tab_selectionModel = new QItemSelectionModel(tab_model);
    tableView->setSelectionModel(tab_selectionModel);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableView);

    setLayout(mainLayout);
    resize(450, 400);

    setWindowTitle("QTableView 샘플");
    SetHeader();
    tableAddData();
    createAction();
}

void Window::SetHeader()
{
    tab_model->setHeaderData(0, Qt::Horizontal, codec->toUnicode("이름"));
    tab_model->setHeaderData(1, Qt::Horizontal, codec->toUnicode("국어"));
    tab_model->setHeaderData(2, Qt::Horizontal, codec->toUnicode("영어"));
    tab_model->setHeaderData(3, Qt::Horizontal, codec->toUnicode("수학"));
}

void Window::tableAddData()
{
    struct dsearch_entry dsentry;
    list<DSEARCH_ENTRY>::iterator dse = list_dsearch_entry.begin();

    memset(&dsentry, 0x00, sizeof(dsentry));
    strcpy(dsentry.name, "홍길동");
    dsentry.kor = 80;
    dsentry.eng = 95;
    dsentry.math = 88;

    advance(dse, 0);

    list_dsearch_entry.insert(dse, dsentry);

    tab_model->insertRows(0, 1, QModelIndex());
    tab_model->setData(tab_model->index(0,0,QModelIndex()), codec->toUnicode(dsentry.name));
    tab_model->setData(tab_model->index(0,1,QModelIndex()), QString("%1").arg(dsentry.kor));
    tab_model->setData(tab_model->index(0,2,QModelIndex()), QString("%1").arg(dsentry.eng));
    tab_model->setData(tab_model->index(0,3,QModelIndex()), QString("%1").arg(dsentry.math));

    memset(&dsentry, 0x00, sizeof(dsentry));
    strcpy(dsentry.name, "이순신");
    dsentry.kor = 75;
    dsentry.eng = 43;
    dsentry.math = 65;

    //advance(dse, 1);
    list_dsearch_entry.insert(dse, dsentry);

    tab_model->insertRows(1, 1, QModelIndex());
    tab_model->setData(tab_model->index(1,0,QModelIndex()), codec->toUnicode(dsentry.name));
    tab_model->setData(tab_model->index(1,1,QModelIndex()), QString("%1").arg(dsentry.kor));
    tab_model->setData(tab_model->index(1,2,QModelIndex()), QString("%1").arg(dsentry.eng));
    tab_model->setData(tab_model->index(1,3,QModelIndex()), QString("%1").arg(dsentry.math));
}

void Window::createAction()
{
    connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tab_click(QModelIndex)));
}

void Window::slot_tab_click(const QModelIndex &index)
{
    struct dsearch_entry dsentry;

    qDebug("INDEX ROWS : %d", index.row());
    qDebug("INDEX COLUMN: %d", index.column());

    list<DSEARCH_ENTRY>::iterator dse = list_dsearch_entry.begin();
    advance(dse, index.row());

    dsentry = *dse;

    if(index.column() == 0) {
        QMessageBox::warning(this, "QTableView Example", QString("%1").arg(codec->toUnicode(dsentry.name)));
    } else if(index.column() == 1) {
        QMessageBox::warning(this, "QTableView Example", QString("%1").arg(dsentry.kor));
    } else if(index.column() == 2) {
        QMessageBox::warning(this, "QTableView Example", QString("%1").arg(dsentry.eng));
    } else if(index.column() == 3) {
        QMessageBox::warning(this, "QTableView Example", QString("%1").arg(dsentry.math));
    } else {
        qDebug("noting!!!!");
    }
}
