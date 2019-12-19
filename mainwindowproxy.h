﻿#ifndef MAINWINDOWPROXY_H
#define MAINWINDOWPROXY_H

#include <QObject>
#include <QThread>
#include <QProcess>
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
    void writeFavor(QString title, QString data, QString abstract, QString address, bool type);
    void startCrawler();
    void getClawlerOutput();
signals:
    void addNewsItemToUI(QString title, QString data, QString abstract, QString address, bool needFavor);
    void clearNewsinUI();
    void wait();
    void stopwait();
    void startPython(QStringList websitelist);
    void pythonEnd(QString website);
protected:
    virtual void run();
private:
    MainWindow *mainwindow;
    QProcess *process;
};

#endif // MAINWINDOWPROXY_H
