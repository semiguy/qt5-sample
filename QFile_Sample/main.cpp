#include <QApplication>
#include <QStyleFactory>

#include "mywidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyWidget widget;

    QStringList styles = QStyleFactory::keys();
    app.setStyle(styles[3]);

    widget.show();

    return app.exec();
}
