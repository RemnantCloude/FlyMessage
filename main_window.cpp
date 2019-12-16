﻿#include <QtWidgets/QVBoxLayout>
#include <QFontDatabase>
#include <QDebug>
#include <QCoreApplication>
#include <QStyleOption>
#include <QPainter>

#include "main_window.h"

#define ADDNEWS     true
#define DELETENEWS  false

MainWindow::MainWindow(FM_Setting *se, QWidget *parent) : 
    QWidget(parent),
    settings(se)
{
    setAttribute(Qt::WA_StyledBackground,true);
    
    now_website = "全部新闻";
    news_amounts = 10;

    setThisLayout();
    setThisStyle();
}

MainWindow::~MainWindow()
{    
}

void MainWindow::setThisLayout()
{
    thislayout = new QVBoxLayout(this);
    this->setLayout(thislayout);
    thislayout->setSpacing(0);
    
    sbImage = new QLabel(this);
    sbImage->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred));
    sbImage->setAlignment(Qt::AlignCenter);
    sbImage->setPixmap(QPixmap(":/images/sb"));
    thislayout->addWidget(sbImage);
    

    tipLabel = new QLabel("这里空空如也~",this);
    tipLabel->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred));
    tipLabel->setAlignment(Qt::AlignCenter);
    tipLabel->setStyleSheet("font-family: \"微软雅黑\"; font-size: 48px; color:black; text-align: center;");
    thislayout->addWidget(tipLabel,0,Qt::AlignVCenter);
    
    tip2Label = new QLabel("已经到底了~",this);
    tip2Label->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred));
    tip2Label->setAlignment(Qt::AlignCenter);
    tip2Label->setStyleSheet("font-family: \"微软雅黑\"; font-size: 24px; color:gray; text-align: center;");
    thislayout->addWidget(tip2Label);
    tip2Label->hide();
    
    newsSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    thislayout->addItem(newsSpacer);
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
                        "MainWindow {background : rgba(255,255,255,50);}"
                        "QLabel{font-family:\"微软雅黑\";font:13pt}");

}

void MainWindow::nullPageJudge()
{
    if(newsArray.size() == 0)
    {
        tipLabel->show();
        sbImage->show();
        tip2Label->hide();
    }
    else {
        tipLabel->hide();
        sbImage->hide();
        tip2Label->show();
    }
}

void MainWindow::addNewsItem(QString a, QString b, QString c, QString d, bool needFavor)
{
    News *news = new News(this,a,b,c,d,needFavor);
    newsArray.append(news);
    
    news->setCursor(Qt::PointingHandCursor);
    thislayout->insertWidget(newsArray.size()*2,news);
    thislayout->insertWidget(newsArray.size()*2+1,news->line);
    
    //update();

    connect(news, SIGNAL(FavorNews(bool)), this, SLOT(onFavorNews(bool)));
    
    nullPageJudge();
}

void MainWindow::clearNews()
{
    foreach(News *news, newsArray)
    {
        delete news;
        newsArray.pop_back();
    }
    nullPageJudge();
}

void MainWindow::refreshAllNews()
{
    clearNews();
}

void MainWindow::onRefreshNews(QString website)
{
    clearNews();
    now_website = website;
    if(website!="全部新闻")
        emit getNews(now_website);
    else
        refreshAllNews();
}

void MainWindow::onRefreshNews()
{
    clearNews();
    emit getNews(now_website);
}

void MainWindow::deleteNews(News *news)
{
    newsArray.removeOne(news);
    delete news;
}

void MainWindow::onFavorNews(bool type)
{
    News *news = dynamic_cast<News*>(sender());//获取信号发送者的指针
    writeFavor(news->title_Lab->text(),
               news->time_Lab->text(),
               news->type_Lab->text(),
               news->abstract_Lab->text(),
               type);
    //收藏夹状态删除条目
    if(type == false && pageState == PageState::FavorPage){
        deleteNews(news);
    }
    nullPageJudge();
}
