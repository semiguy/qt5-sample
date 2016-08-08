#include "blockingclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlockingClient client;
    client.show();

    return a.exec();
}
