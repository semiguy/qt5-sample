#include <QApplication>
#include <QtGui>
#include <QDirModel>
#include <QTreeView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QDirModel model;
    QTreeView tree;
    tree.setModel(&model);

    tree.setAnimated(false);
    tree.setIndentation(20);
    tree.setSortingEnabled(true);

    tree.setWindowTitle(QObject::tr("Dir View"));
    tree.resize(640,480);
    tree.show();

    return app.exec();
}
