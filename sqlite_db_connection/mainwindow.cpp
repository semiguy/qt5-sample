#include <QtGui>
#include <QtSql>

#include "add_dlg.h"
#include "modify_dlg.h"
#include "mainwindow.h"

#include <QHBoxLayout>
#include <QList>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow()
{
    init();
    create_toolbar();
    create_mainWidget();
    create_action();

    qDebug() << QSqlDatabase::drivers() << endl;
    db_connect();

    setWindowTitle(codec->toUnicode("주소관리"));
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

    ToolBar_add = new QAction(QIcon(":/images/add.png"), codec->toUnicode("등록"), this);
    ToolBar_add->setShortcut(tr("Ctrl+A"));
    ToolBar_add->setStatusTip(codec->toUnicode("등록"));

    ToolBar_close = new QAction(QIcon(":/images/close.png"), codec->toUnicode("종료"), this);
    ToolBar_close->setShortcut(tr("Ctrl+H"));
    ToolBar_add->setStatusTip(codec->toUnicode("종료"));

    ToolBar->addAction(ToolBar_add);
    ToolBar->addAction(ToolBar_close);

    ToolBar_add->setEnabled(true);
    ToolBar_close->setEnabled(true);
}

/**
 * mainWidget
 * @brief MainWindow::create_mainWidget
 */
void MainWindow::create_mainWidget()
{
    comboBox = new QComboBox();

    comboBox->addItem(codec->toUnicode("전체검색"));
    comboBox->addItem(codec->toUnicode("이름"));
    comboBox->addItem(codec->toUnicode("연락처"));
    comboBox->addItem(codec->toUnicode("주소"));

    lineEdit = new QLineEdit();
    pushButton = new QPushButton(codec->toUnicode("검색"));
    pushButton_modify = new QPushButton(codec->toUnicode("수정"));
    pushButton_del = new QPushButton(codec->toUnicode("삭제"));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(comboBox);
    hLayout->addWidget(lineEdit);
    hLayout->addWidget(pushButton);

    QHBoxLayout *hLayout_bottom = new QHBoxLayout;
    hLayout_bottom->addWidget(pushButton_modify);
    hLayout_bottom->addWidget(pushButton_del);

    tab_model = new QStandardItemModel(0,4,this);
    table_view = new QTableView;
    table_view->setModel(tab_model);

    tab_model->setHeaderData(0, Qt::Horizontal, codec->toUnicode("번호"));
    tab_model->setHeaderData(1, Qt::Horizontal, codec->toUnicode("이름"));
    tab_model->setHeaderData(2, Qt::Horizontal, codec->toUnicode("연락처"));
    tab_model->setHeaderData(3, Qt::Horizontal, codec->toUnicode("주소"));

    table_view->setColumnWidth(0,80);
    table_view->setColumnWidth(1,100);
    table_view->setColumnWidth(2,150);
    table_view->setColumnWidth(3,320);

    tab_selectionModel = new QItemSelectionModel(tab_model);
    table_view->setSelectionModel(tab_selectionModel);
    table_view->setSelectionBehavior(QAbstractItemView::SelectRows);

    main_page = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(main_page);
    mainLayout->setSpacing(1);
    mainLayout->setMargin(1);
    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(table_view);
    mainLayout->addLayout(hLayout_bottom);

    setCentralWidget(main_page);
}

void MainWindow::db_connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("qttest.db");

    if(!db.open()) {
        statusBar()->showMessage(codec->toUnicode("DB 접속 실패 하였습니다."));
    } else {
        statusBar()->showMessage(codec->toUnicode("DB에 접속 하였습니다."));
    }
}

void MainWindow::create_action()
{
    connect(ToolBar_add, SIGNAL(triggered(bool)), this, SLOT(slot_ToolBar_add()));
    connect(ToolBar_close, SIGNAL(triggered(bool)), this, SLOT(slot_ToolBar_close()));
    connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(slot_pushButton()));
    connect(pushButton_modify, SIGNAL(clicked(bool)), this, SLOT(slot_pushButton_modify()));
    connect(pushButton_del, SIGNAL(clicked(bool)), this, SLOT(slot_pushButton_del()));
    connect(table_view, SIGNAL(clicked(const QModelIndex)),this, SLOT(slot_table_view(QModelIndex)));
}

void MainWindow::slot_ToolBar_add()
{
    add_dlg *add_dialog = new add_dlg(this);

    if(add_dialog->exec() == QDialog::Accepted) {
        statusBar()->showMessage(codec->toUnicode("등록완료"));
    }
}

void MainWindow::slot_ToolBar_close()
{
    close();
}

void MainWindow::slot_pushButton()
{
    qDebug("current : %d", comboBox->currentIndex());
    QSqlQuery query;
    QString text;

    if(comboBox->currentIndex() == 0) {
        // 전체 검색
        text = QString("select * from address");
    } else if(comboBox->currentIndex() == 1) {
        // 이름 검색
        text = QString("select * from address where name like '%%1%'").arg(lineEdit->text());
    } else if(comboBox->currentIndex() == 2) {
        // 연락처 검색
        text = QString("select * from address where tel like '%%1%'").arg(lineEdit->text());
    } else if(comboBox->currentIndex() == 3) {
        // 주소 검색
        text = QString("select * from address where address like '%%1%'").arg(lineEdit->text());
    } else {
        // nothing
        qDebug("check comboBox->currentIndex()");
    }

    int size = tab_model->rowCount();
    tab_model->removeRows(0, size, QModelIndex());

    QMessageBox::warning(this, "SQL", text);
    query.exec(codec->fromUnicode(text));

    int i=0;
    while(query.next()) {
        QByteArray num = query.value(0).toByteArray();
        QByteArray name = query.value(1).toByteArray();
        QByteArray tel = query.value(2).toByteArray();
        QByteArray address = query.value(3).toByteArray();

        tab_model->insertRows(i, 1, QModelIndex());
        tab_model->setData(tab_model->index(i, 0, QModelIndex()), codec->toUnicode(num));
        tab_model->setData(tab_model->index(i, 1, QModelIndex()), codec->toUnicode(name));
        tab_model->setData(tab_model->index(i, 2, QModelIndex()), codec->toUnicode(tel));
        tab_model->setData(tab_model->index(i, 3, QModelIndex()), codec->toUnicode(address));
        //tab_model->setData(tab_model->index(i, 3, QModelIndex()), address);

        i++;
    }

    QString temp = QString("%1%2").arg(i).arg(codec->toUnicode("건의 레코드가 검색되었습니다."));

    statusBar()->showMessage(temp);
}

void MainWindow::slot_table_view(const QModelIndex &index) {
    int row = index.row();

    QModelIndex index2 = index.sibling(row,0);
    selected_num = tab_model->data(index2, Qt::DisplayRole).toInt();

    //statusBar()->showMessage(num);
}

void MainWindow::slot_pushButton_modify()
{
    QList<QModelIndex> list;
    QModelIndex index;

    list = tab_selectionModel->selectedIndexes();

    if(list.size() == 0) {
        QMessageBox::warning(this, "Warning", codec->toUnicode("수정할 데이터를 선택해 주세요."));
    } else {
        qDebug("selected number : %d", selected_num);
        modify_dlg modify_dialog(this, selected_num);

        if(modify_dialog.exec() == QDialog::Accepted) {
            statusBar()->showMessage(codec->toUnicode("수정완료"));
        }
    }
}

void MainWindow::slot_pushButton_del()
{
    QList<QModelIndex> list;
    QModelIndex index;

    list = tab_selectionModel->selectedIndexes();

    if(list.size() == 0) {
        QMessageBox::warning(this, "Warning", codec->toUnicode("삭제할 데이터를 선택해 주세요."));
    } else {
        QMessageBox msgBox;
        msgBox.setText(codec->toUnicode("주소삭제"));
        msgBox.setInformativeText(codec->toUnicode("정말로 삭제 하시겠습니까?"));
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int ret = msgBox.exec();

        QString text;
        QSqlQuery query;

        switch(ret) {
        case QMessageBox::Yes:
            text = QString("delete from address where num=%1").arg(selected_num);
            query.exec(text);
            break;

        case QMessageBox::No:
            break;
        default:
            break;
        }
    }
}
