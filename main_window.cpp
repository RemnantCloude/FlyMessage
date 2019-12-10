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

#define BTN_WIDTH   (600)
#define BTN_HEIGHT  (100)

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    website = "website1";//初始化
    news_amounts = 10;

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
//    setAttribute(Qt::WA_StyledBackground,true);

    //用不了
//    QString qss;
//    QFile qssFile(":/qss/main_window");
//    qssFile.open(QFile::ReadOnly);

//    if(qssFile.isOpen())
//    {
//        qDebug()<<"open successfully";
//        qss = QLatin1String(qssFile.readAll());
//        this->setStyleSheet(qss);
//        qssFile.close();
//    }
    //可以用
//    QFile file(":/qss/main_window");
//    file.open(QFile::ReadOnly);
//    QTextStream filetext(&file);
//    QString stylesheet = filetext.readAll();
//    this->setStyleSheet(stylesheet);
//    file.close();

    thislayout->setSpacing(0);
    this->setStyleSheet("News {background: rgb(243,243,243)}"
                        "News:hover {background: rgb(220,220,220)}"
                        "MainWindow {background : rgb(243,243,243)}"
                        "QLabel{font-family:\"微软雅黑\";font:13pt}");
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(500, 0));
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
                News *news = new News(this,array1.at(0).toString(),array1.at(1).toString(),array1.at(2).toString(),array1.at(3).toString());
                news->setCursor(Qt::PointingHandCursor);
                thislayout->addWidget(news);
                thislayout->addWidget(news->line);

                count++;
            }
            count = 0;//清零
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

void MainWindow::onRefresh(bool)
{
    //清空新闻
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

    getNews(website);
}
