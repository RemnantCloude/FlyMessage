#ifndef MAINWINDOWPROXY_H
#define MAINWINDOWPROXY_H

#include <QObject>
#include <QThread>
#include "main_window.h"

class MainWindowProxy : public QObject
{
    Q_OBJECT
public:
    MainWindowProxy(MainWindow *mainwindow,QObject *parent = nullptr);
    void getNews(QString web);
    void getFavorNews();
public slots:
    void threadStarted();
    void threadFinished();
    void writeFavor(QString s1, QString s2, QString s3, QString s4, bool type);
signals:
    void addNewsItemToUI(QString a, QString b, QString c, QString d, bool needFavor);
    void clearNewsinUI();
    void wait();
    void stopwait();
protected:
    virtual void run();
private:
    MainWindow *mainwindow;
};

#endif // MAINWINDOWPROXY_H
