#include "server.h"
#include <QApplication>
#include <QtCore>

#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;
    server.show();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    return a.exec();
}
