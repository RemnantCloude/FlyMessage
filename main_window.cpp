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
