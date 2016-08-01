#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 메뉴바
    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;

    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered(bool)), this, SLOT(open()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);

    // 툴바
    QToolBar *fileToolBar;
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);

    // Dock Widget
    QDockWidget *dock = new QDockWidget(tr("Target"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QListWidget *customerList = new QListWidget(dock);
    customerList->addItems(QStringList() << "One" << "Two" << "Three" << "Four" << "Five");
    dock->setWidget(customerList);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    // Central Widget
    QTextEdit *textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    // Status Bar
    statusBar()->showMessage(tr("Ready"));

}

void MainWindow::newFile()
{

}

void MainWindow::open()
{

}

MainWindow::~MainWindow()
{

}
