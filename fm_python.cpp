#include <QProcess>
#include <iostream>
#include <QDebug>
#include "fm_python.h"

FM_Python::FM_Python(QObject *parent) : QObject(parent)
{


}

void FM_Python::execPython()
{
    QString my_process_2 = "./test.exe";
    process = new QProcess();

    qDebug()<<my_process_2;
    QStringList argument;

    process->start(my_process_2);
    if (!process->waitForStarted())
    {
        qDebug() << "启动失败";

    }

    connect(process,SIGNAL(readyRead()),this,SLOT(Fctn_get_info()));
}

void FM_Python::Fctn_get_info()
{
    qDebug() << "fuck me \n" << process->readAll();
}

