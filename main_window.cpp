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
    foreach(News *news, newsArray)
    {
        delete news;
    }
    delete tipLabel;
    delete tip2Label;
    delete sbImage;
    delete thislayout;
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
    tipLabel->setStyleSheet("font-family: \"微软雅黑\"; font-size: 48px; color:gray; text-align: center;");
    thislayout->addWidget(tipLabel);
    
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
                        "MainWindow {background : rgb(255,255,255);}"
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

void MainWindow::getNews(QString web)
{
    QVector<QString> column_str;
    QVector<bool>    column_bool;
    
    settings->get_web_columns(web,column_str,column_bool);
    int max_display_news = settings->get_max_display_news();

    //获取新闻内容
    QJsonObject news = readJson("./news.json");
    QJsonObject news_type = news.value(web).toObject();
    for(int i = 0; i < column_str.size(); i++)
    {
        if(column_bool[i])
        {
            QJsonArray array = news_type.value(column_str[i]).toArray();//网站新闻
            for(int i = 0;i < array.size() && i < max_display_news; i++)
            {
                QJsonArray array1 = array.at(i).toArray();//单条新闻
                
                addNewsItem(array1.at(0).toString(),
                            array1.at(1).toString(),
                            array1.at(2).toString(),
                            array1.at(3).toString(),
                            true);                
            }
        }
    }
    pageState = PageState::OtherPage;
}

void MainWindow::getFavorNews()
{
    clearNews();

    QJsonObject favor = readJson("./favorite.json");
    QJsonArray array = favor.value("favorite").toArray();
    for(int i = 0; i < array.size(); i++)
    {
        QJsonArray array1 = array.at(i).toArray();//单条新闻
        addNewsItem(array1.at(0).toString(),
                    array1.at(1).toString(),
                    array1.at(2).toString(),
                    array1.at(3).toString(),
                    false);

    }
    pageState = PageState::FavorPage;
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
        getNews(website);
    else
        refreshAllNews();
}

void MainWindow::onRefreshNews()
{
    clearNews();
    getNews(now_website);
}

void MainWindow::deleteNews(News *news)
{
    newsArray.removeOne(news);
    delete news;
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
    //收藏夹状态删除条目
    if(type == false && pageState == PageState::FavorPage){
        deleteNews(news);
    }
    nullPageJudge();
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
