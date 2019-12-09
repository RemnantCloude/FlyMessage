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

#include "main_window.h"
#include "news.h"

#define BTN_WIDTH   (600)
#define BTN_HEIGHT  (100)

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setThisLayout();
    setThisStyle();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setThisLayout()
{
    thislayout = new QVBoxLayout();
    this->setLayout(thislayout);
    thislayout->setSpacing(0);
}

void MainWindow::setThisStyle()
{
    this->setStyleSheet("News {background: white}"
                        "News:hover {border:1px solid blue; background: #d9fdff;}"
                        "MainWindow {background : white;}");
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
    QJsonObject settings = readJson("./wa.json");

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
    for(int i = 0; i < settings_type.size(); i++)
    {
        if( settings_type.value(settings_str.at(i)).toBool() == true)//板块匹配
        {
            QJsonArray array = news_type.value(settings_str.at(i)).toArray();//网站新闻
            for(int i = 0; i < array.size(); i++)
            {
                QJsonArray array1 = array.at(i).toArray();//单条新闻
                News *news = new News(this,array1.at(0).toString(),array1.at(1).toString(),array1.at(2).toString(),array1.at(3).toString());
                news->setCursor(Qt::PointingHandCursor);
                thislayout->addWidget(news);
                thislayout->addWidget(news->line);
            }
        }
    }
    //setThisStyle();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}
