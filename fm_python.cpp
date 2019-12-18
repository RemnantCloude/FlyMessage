#include <QProcess>
#include <iostream>
#include <QDebug>
#include <QTextCodec>
#include "fm_python.h"

FM_Python::FM_Python(QObject *parent) : QObject(parent)
{

}

void FM_Python::execPython(QStringList websitelist)
{
    process = new QProcess;
    process->start("./crawler.exe", websitelist);
    if (!process->waitForStarted())
    {
        qDebug() << "爬虫启动失败";
    }
    connect(process,SIGNAL(readyRead()),this,SLOT(getClawlerOutput()));
}

void FM_Python::getClawlerOutput()
{
    QByteArray data = process->readAll();
    QString string = QTextCodec::codecForMib(106)->toUnicode(data);//106:UTF-8
    if( string == "done\r\n")
    {
        emit pythonEnd();
    }
    else
    {
        qDebug() << "爬虫爬取失败";
    }
    process->close();
    disconnect(process,SIGNAL(readyRead()),this,SLOT(getClawlerOutput()));
    delete process;
}

