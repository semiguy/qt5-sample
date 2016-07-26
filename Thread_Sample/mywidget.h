#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMainWindow>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QAction>
#include <QActionGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class mythread: public QThread
{
private:
    bool mt_stop;
    bool mt_pause;

    QWaitCondition mt_pauseCondition;
public:
    QMutex mutex;

    mythread()
    {
        mt_stop = false;
        mt_pause = false;
    }

    void pause()
    {
        mt_pause = true;
    }

    void resume()
    {
        mt_pause = false;
        mt_pauseCondition.wakeAll();
    }

    void stop()
    {
        mt_stop = true;
    }

    void run()
    {
        qDebug("QThread Start");

        while(1) {
            sleep(1);
            mutex.lock();
            if(mt_stop) break;
            if(mt_pause) {
                qDebug("QThread Pause...");
                mt_pauseCondition.wait(&mutex);
                qDebug("QThread Resume...");
            }
            mutex.unlock();

            qDebug("Thread running...");
        }

        qDebug("Thread stop...");
    }
};

class MyWidget : public QMainWindow
{
    Q_OBJECT

public:
    MyWidget();
    mythread my_thread;

private:
    QWidget *main_page;
    QPushButton *pbt_start;
    QPushButton *pbt_pause;
    QPushButton *pbt_resume;
    QPushButton *pbt_stop;

private slots:
    void slot_pbt_start();
    void slot_pbt_pause();
    void slot_pbt_resume();
    void slot_pbt_stop();
};

#endif // MYWIDGET_H
