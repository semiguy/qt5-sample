#include <QApplication>
#include <QStyleFactory>

#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList styles = QStyleFactory::keys();

    app.setStyle(styles[3]);

    Window window;
    window.show();

    return app.exec();
}
