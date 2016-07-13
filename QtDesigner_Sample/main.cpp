#include <QApplication>

#include "testform.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TestForm TestFormWindow;
    TestFormWindow.show();

    return app.exec();
}
