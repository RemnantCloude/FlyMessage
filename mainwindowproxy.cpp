#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QDebug>
#include <QThread>

#include "mainwindowproxy.h"

#define ADDNEWS     true
#define DELETENEWS  false

MainWindowProxy::MainWindowProxy(MainWindow *mw,QObject *parent)
    :QObject (parent),
     mainwindow(mw)
{
    
}

void MainWindowProxy::threadStarted(void)
{
    qDebug()<< "Thread has started...ID is:" << QThread::currentThreadId();
}
void MainWindowProxy::threadFinished(void)
{
    qDebug()<< "Thread has stopped Id is:" << QThread::currentThreadId();
}

void MainWindowProxy::run()
{
    
}

void MainWindowProxy::getNews(QString web)
{
    QVector<QString> column_str;
    QVector<bool>    column_bool;
    //等待界面
    emit wait();
    
    mainwindow->settings->get_web_columns(web,column_str,column_bool);
    int max_display_news = mainwindow->settings->get_max_display_news();
    //获取新闻内容
    QJsonObject news = readJson("./news.json");
    QJsonObject news_type = news.value(web).toObject();
    QThread::msleep(300);
    for(int i = 0; i < column_str.size(); i++)
    {
        if(column_bool[i])
        {
            QJsonArray array = news_type.value(column_str[i]).toArray();//网站新闻
            for(int i = 0;i < array.size() && i < max_display_news; i++)
            {
                QJsonArray array1 = array.at(i).toArray();//单条新闻
                
                emit addNewsItemToUI(array1.at(0).toString(),
                                     array1.at(1).toString(),
                                     array1.at(2).toString(),
                                     array1.at(3).toString(),
                                     true);
                QThread::msleep(10);
            }
        }
    }
    mainwindow->pageState = PageState::OtherPage;
    //关闭等待界面
    emit stopwait();
}

void MainWindowProxy::getFavorNews()
{
    emit clearNewsinUI();
    
    QJsonObject favor = readJson("./favorite.json");
    QJsonArray array = favor.value("favorite").toArray();
    for(int i = 0; i < array.size(); i++)
    {
        QJsonArray array1 = array.at(i).toArray();//单条新闻
        emit addNewsItemToUI(array1.at(0).toString(),
                             array1.at(1).toString(),
                             array1.at(2).toString(),
                             array1.at(3).toString(),
                             false);
    }
    mainwindow->pageState = PageState::FavorPage;
}

void MainWindowProxy::writeFavor(QString s1,QString s2,QString s3,QString s4,bool type)
{
    QJsonArray array;
    array.insert(0, s1);
    array.insert(1, s2);
    array.insert(2, s3);
    array.insert(3, s4);
    writeJson("./favorite.json", array, type);
}

QJsonObject MainWindowProxy::readJson(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text); // 只读文件
    QString value = file.readAll();
    file.close();

    // 错误提示
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<"解析json文件错误!";
    }
    QJsonObject jsonObject = document.object();

    return jsonObject;
}

void MainWindowProxy::writeJson(QString filename, QJsonArray news, bool type)
{
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QString value = file.readAll();
    file.resize(0);

    // 错误提示
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<"解析json文件错误!";
    }
    QJsonObject jsonObject = document.object();

    //获取新闻
    QJsonArray array = jsonObject.take("favorite").toArray();

    if(type == ADDNEWS)//增加
    {
        array.append(news);
    }
    else//删除
    {
        for(int i = 0; i < array.size(); i++)
        {
            if(array.at(i).toArray() == news)
            {
                array.takeAt(i);
                break;
            }
        }
    }
    jsonObject.insert("favorite", array);//添加到对象中
    document.setObject(jsonObject);
    file.write(document.toJson());
    file.close();
}
