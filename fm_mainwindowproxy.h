﻿#ifndef MAINWINDOWPROXY_H
#define MAINWINDOWPROXY_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include "fm_mainwindow.h"

class FM_MainWindowProxy : public QObject
{
    Q_OBJECT
public:
    FM_MainWindowProxy(FM_MainWindow *mainwindow,QObject *parent = nullptr);
    void getNews(QString web);
    void getFavorNews();
public slots:
    void threadStarted();
    void threadFinished();
    void writeFavor(QString title, QString data, QString abstract, QString address, bool type);
    void startNewsCrawler();
    void startNoticeCrawler();
signals:
    void addNewsItemToUI(QString title, QString data, QString abstract, QString address, bool needFavor);
    void clearNewsinUI();
    void wait();
    void stopwait();
    void startPython(QStringList websitelist);
    void pythonEnd();
    void inform_notice();
protected:
    virtual void run();
private:
    FM_MainWindow *mainwindow;
    QProcess *process;
    QVector<QString> crawler_Weblist;

    void crawler(QStringList web);
};

#endif // MAINWINDOWPROXY_H
