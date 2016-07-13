#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QTableView>
#include <QAction>
#include <QModelIndex>


#include <list>
using namespace std;

/*
QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QItemSelectionModel;
class QTableView;
class QAction;
class QModelIndex;
QT_END_NAMESPACE
*/
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    void SetHeader();
    void tableAddData();
    void createAction();

private slots:
    void slot_tab_click(const QModelIndex &index);

private:
    struct dsearch_entry
    {
        char name[40];
        unsigned int kor;
        unsigned int eng;
        unsigned int math;
    };

    typedef struct dsearch_entry DSEARCH_ENTRY;
    list<DSEARCH_ENTRY> list_dsearch_entry;

    QTextCodec *codec;
    QAbstractItemModel *tab_model;
    QTableView *tableView;
    QItemSelectionModel *tab_selectionModel;
};

#endif // WINDOW_H
