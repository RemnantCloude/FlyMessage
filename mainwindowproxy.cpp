#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QDebug>
#include <QThread>
#include <QTextCodec>

#include "mainwindowproxy.h"
#include "json.h"

#define ADDNEWS true
#define DELETENEWS false

MainWindowProxy::MainWindowProxy(MainWindow *mw, QObject *parent)
    : QObject(parent),
      mainwindow(mw)
{
}

void MainWindowProxy::threadStarted(void)
{
    qDebug() << "Thread has started...ID is:" << QThread::currentThreadId();
}
void MainWindowProxy::threadFinished(void)
{
    qDebug() << "Thread has stopped Id is:" << QThread::currentThreadId();
}

void MainWindowProxy::run()
{
}

void MainWindowProxy::getNews(QString web)
{
    QVector<QString> column_str;
    QVector<bool> column_bool;
    //等待界面
    emit wait();
    QThread::msleep(300);
    mainwindow->settings->get_web_columns(web, column_str, column_bool);
    int max_display_news = mainwindow->settings->get_max_display_news();
    //获取新闻内容
    QJsonObject news = FM_Json::readJson("./" + web + ".json").object();
    QJsonObject news_type = news.value(web).toObject();

    for (int i = 0; i < column_str.size(); i++)
    {
        if (column_bool[i])
        {
            QJsonArray array = news_type.value(column_str[i]).toArray(); //网站新闻
            for (int i = 0; i < array.size() && i < max_display_news; i++)
            {
                QJsonArray array1 = array.at(i).toArray(); //单条新闻

                emit addNewsItemToUI(array1.at(0).toString(),
                                     array1.at(1).toString(),
                                     array1.at(2).toString(),
                                     array1.at(3).toString(),
                                     true);
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

    QJsonObject favor = FM_Json::readJson("./favorite.json").object();
    QJsonArray array = favor.value("favorite").toArray();
    for (int i = 0; i < array.size(); i++)
    {
        QJsonArray array1 = array.at(i).toArray(); //单条新闻
        emit addNewsItemToUI(array1.at(0).toString(),
                             array1.at(1).toString(),
                             array1.at(2).toString(),
                             array1.at(3).toString(),
                             false);
    }
    mainwindow->pageState = PageState::FavorPage;
}

void MainWindowProxy::writeFavor(QString title, QString data, QString abstract, QString address, bool type)
{
    QJsonArray array;
    array.insert(0, title);
    array.insert(1, data);
    array.insert(2, abstract);
    array.insert(3, address);
    FM_Json::writeJson("./favorite.json", array, type);
}

void MainWindowProxy::startCrawler()
{
    QStringList websitelist;
    if (mainwindow->now_website == "全部新闻")
    {
        websitelist.append("人民网"); //TODO 多线程
        websitelist.append("新浪");
        websitelist.append("网易");
        websitelist.append("教务处");
    }
    else
    {
        websitelist.append(mainwindow->now_website);
    }

    process = new QProcess;
    process->start("./crawler.exe", websitelist);
    if (!process->waitForStarted())
    {
        qDebug() << "爬虫启动失败";
    }
    connect(process,SIGNAL(readyRead()),this,SLOT(getClawlerOutput()));
}

void MainWindowProxy::getClawlerOutput()
{
    QByteArray data = process->readAll();
    QString string = QTextCodec::codecForMib(106)->toUnicode(data);//106:UTF-8
    if( string == "done\r\n")
    {
        emit pythonEnd("全部新闻");
    }
    else
    {
        qDebug() << "爬虫爬取失败";
    }
    process->close();
    disconnect(process,SIGNAL(readyRead()),this,SLOT(getClawlerOutput()));
    delete process;
}
