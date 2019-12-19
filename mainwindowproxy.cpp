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

void MainWindowProxy::updateWeblist()
{
    // 获取要刷新的新闻网站
    if (mainwindow->now_website == "全部新闻")
        mainwindow->settings->get_web_list(crawler_Weblist);
    else
        crawler_Weblist.append(mainwindow->now_website);

    // 分别爬取每个网站
    while (crawler_Weblist.size() != 0)
    {
        QStringList web;
        web.append(crawler_Weblist.takeAt(0));

        process = new QProcess;
        process->start("./crawler.exe", web);
        if (!process->waitForStarted())
        {
            qDebug() << "爬虫启动失败";
        }
        if(process->waitForFinished(-1))
        {
            QByteArray data = process->readAll();
            QString string = QTextCodec::codecForMib(106)->toUnicode(data);//106:UTF-8
            if( string != "done\r\n")
            {
                qDebug() << "爬虫爬取失败";
            }
            process->close();
            delete process;
        }
    }
    emit pythonEnd();
}
