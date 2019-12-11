#include <QtWidgets/QVBoxLayout>
#include <QFontDatabase>

#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

#include <QPushButton>

#include <QStyleOption>
#include <QPainter>

#include "main_window.h"

#define ADDNEWS     true
#define DELETENEWS  false

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground,true);
    
    website = "website1";//初始化
    news_amounts = 10;

    setThisLayout();
    setThisStyle();
}

void MainWindow::setThisLayout()
{
    thislayout = new QVBoxLayout();
    this->setLayout(thislayout);
    thislayout->setSpacing(0);
}

void MainWindow::setThisStyle()
{
//可以用
//    QFile file(":/qss/main_window");
//    file.open(QFile::ReadOnly);
//    QTextStream filetext(&file);
//    QString stylesheet = filetext.readAll();
//    this->setStyleSheet(stylesheet);
//    file.close();

    this->setStyleSheet("News {background: rgb(255,255,255)}"
                        "News:hover {border:1px solid blue; background: #d9fdff;}"
                        "MainWindow {background : rgb(255,255,255);}"
                        "QLabel{font-family:\"微软雅黑\";font:13pt}");

}

QJsonObject MainWindow::readJson(QString filename)
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

void MainWindow::writeJson(QString filename, QJsonArray news, bool type)
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

void MainWindow::getFavorNews()
{
    clearNews();

    QJsonObject favor = readJson("./test_favorite.json");
    QJsonArray array = favor.value("favorite").toArray();
    for(int i = 0; i < array.size(); i++)
    {
        QJsonArray array1 = array.at(i).toArray();//单条新闻
        News *news = new News(this,
                              array1.at(0).toString(),
                              array1.at(1).toString(),
                              array1.at(2).toString(),
                              array1.at(3).toString(),
                              false);
        news->setCursor(Qt::PointingHandCursor);
        thislayout->addWidget(news);
        thislayout->addWidget(news->line);
    }
}

void MainWindow::getNews(QString web)
{
    int count = 0;
    //读取设置文件内容
    QJsonObject settings = readJson("./test_settings.json");

    //解析文件
    QJsonObject settings_type = settings.value(web).toObject();
    QStringList settings_str = settings_type.keys();//获得板块名

    //获取新闻内容
    QJsonObject news = readJson("./test_news.json");
    QJsonObject news_type = news.value(web).toObject();
    for(int i = 0; i < settings_type.size(); i++)
    {
        if( settings_type.value(settings_str.at(i)).toBool() == true)//板块匹配
        {
            QJsonArray array = news_type.value(settings_str.at(i)).toArray();//网站新闻
            for(int i = 0; i < array.size() & count < 10; i++)
            {
                QJsonArray array1 = array.at(i).toArray();//单条新闻
                News *news = new News(this,
                                      array1.at(0).toString(),
                                      array1.at(1).toString(),
                                      array1.at(2).toString(),
                                      array1.at(3).toString(),
                                      false);
                news->setCursor(Qt::PointingHandCursor);
                thislayout->addWidget(news);
                thislayout->addWidget(news->line);
                connect(news, SIGNAL(FavorNews(bool)), this, SLOT(onFavorNews(bool)));

                count++;
            }
            count = 0;//清零
        }
    }
}

void MainWindow::clearNews()
{
    QLayoutItem *child;
    while ((child = thislayout->takeAt(0)) != nullptr)
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(nullptr);
        }
        delete child;
    }
}

void MainWindow::onRefreshNews(bool)
{
    clearNews();
    getNews(website);
}

void MainWindow::onFavorNews(bool type)
{
    News *news = dynamic_cast<News*>(sender());//获取信号发送者的指针
    QJsonArray array;
    array.insert(0, news->title_Lab->text());
    array.insert(1, news->time_Lab->text());
    array.insert(2, news->type_Lab->text());
    array.insert(3, news->abstract_Lab->text());

    writeJson("./test_favorite.json", array, type);
}

