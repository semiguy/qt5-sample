#include <QApplication>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QStyleFactory>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStringList styles = QStyleFactory::keys();
    app.setStyle(styles[3]);

    MainWindow mainWin;
    mainWin.resize(600,500);

    QDesktopWidget *desktop = QApplication::desktop();
    int w = desktop->width();
    int h = desktop->height();

    qDebug("desktop->width : %d, desktop->height() : %d", desktop->width(), desktop->height());

    mainWin.move((w-600)/2, (h-500)/2);
    mainWin.show();

    return app.exec();
}
