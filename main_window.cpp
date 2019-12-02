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

    getNews();

    thislayout = new QVBoxLayout();
    for(int i = 0;i < 10;i++)
    {
        News *news = new News(this,"<a href=\"http://www.csdn.net/\">凤凰新闻","2019.2.1","123456");
        thislayout->addWidget(news);
    }
    this->setLayout(thislayout);
    thislayout->setSpacing(0);
    this->setStyleSheet("News {background: white}"
                        "News:hover {border:1px solid blue; background: #d9fdff}"
                        "MainWindow {background : white}");
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(500, 0));
}

MainWindow::~MainWindow()
{

}

void MainWindow::initComponents()
{

}

void MainWindow::initSignalAndSlot()
{

}

void MainWindow::setThisLayout()
{

}

void MainWindow::setThisStyle()
{

}

void MainWindow::mode(bool)
{

}

void MainWindow::getNews()//TODO:
{
    // 读取文件内容
    QFile file("./test_news.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text); // 只读文件
    QString value = file.readAll();
    file.close();

    // TODO:错误提示
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);

    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
//        qDebug()<<tr("解析json文件错误！");
        return ;
    }

    //解析文件
    QJsonObject jsonObject = document.object();
    QStringList website = jsonObject.keys();
    for(int i = 0; i < website.size(); i++)
    {
        qDebug()<<"website"<<i<<"is:"<<website.at(i);
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
