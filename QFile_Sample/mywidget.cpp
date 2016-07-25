#include <QtGui>
#include "mywidget.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>

MyWidget::MyWidget()
{
    setFixedSize(600,500);

    fileMenu = menuBar()->addMenu(tr("&File"));

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("File Open"));

    connect(openAct, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    fileMenu->addAction(openAct);
    fileMenu->addSeparator();

    edit = new QTextEdit("");

    setCentralWidget(edit);

    statusBar()->showMessage(tr("File Open"));
}

void MyWidget::openFile()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", "ALL (*.*)");
    QFile file(fileName);

    if(file.open(QFile::ReadOnly | QFile::Text)) {
        edit->setPlainText(file.readAll());
    }
}
