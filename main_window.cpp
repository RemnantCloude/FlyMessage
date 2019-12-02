#include "main_window.h"
#include "news.h"

#include <QtWidgets/QVBoxLayout>
#include <QFontDatabase>
#include <QScrollArea>

//TEST:
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

#include <QStyleOption>
#include <QPainter>

#define BTN_WIDTH   (600)
#define BTN_HEIGHT  (100)

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setThisLayout();
    setThisStyle();
    getNews("网站1");
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{

}

void MainWindow::initSignalAndSlot()
{

}

void MainWindow::setThisLayout()
{
    thislayout = new QVBoxLayout();
    this->setLayout(thislayout);
}

void MainWindow::setThisStyle()
{
    thislayout->setSpacing(0);
    this->setStyleSheet("News {background: white}"
                        "News:hover {border:1px solid blue; background: #d9fdff}"
                        "MainWindow {background : white}");
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(500, 0));
}

void MainWindow::switchMode(QString web)
{
    website = web;
    getNews(website);
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

void MainWindow::getNews(QString web)//TODO:
{
    //读取设置文件内容
    QJsonObject settings = readJson("./test_settings.json");

    //解析文件
    QJsonObject settings_type = settings.value(web).toObject();
    QStringList settings_str = settings_type.keys();//获得板块名
    for(int i = 0; i < settings_type.size(); i++)
    {
        qDebug()<<settings_str.at(i)<<":"<<settings_type.value(settings_str.at(i)).toBool();
    }

    //获取新闻内容
    QJsonObject news = readJson("./test_news.json");
    QJsonObject news_type = news.value(web).toObject();
    for(int i = 2; i < settings_type.size(); i++)
    {
        if( settings_type.value(settings_str.at(i)).toBool() == true)//板块匹配
        {
            QJsonArray array = news_type.value(settings_str.at(i)).toArray();//网站新闻
            for(int i = 0; i < array.size(); i++)
            {
                QJsonArray array1 = array.at(i).toArray();//单条新闻
                News *news = new News(this,array1.at(0).toString(),array1.at(1).toString(),array1.at(2).toString(),array1.at(3).toString());
                thislayout->addWidget(news);
            }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}
