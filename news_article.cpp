#include "news_article.h"

#include <QtWidgets/QTextEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QFontDatabase>

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

#include <QSettings>

#define BTN_WIDTH   (600)
#define BTN_HEIGHT  (100)

NewsArticle::NewsArticle(QWidget *parent) : QWidget(parent)
{
    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽

    setThisLayout();
    setThisStyle();

    //TEST:
    // QSettings settings("./settings.ini", QSettings::IniFormat);
    // if(!settings.isWritable())
    //     qDebug()<<"Cant read settings"<<endl;
    // settings.setValue("test/margin", "微软");
    // settings.sync();
    // settings.beginGroup("test");
    // news1_Tex->setText(settings.value("margin").toString());
    // settings.endGroup();
//    json();
}

NewsArticle::~NewsArticle()
{

}

void NewsArticle::initComponents()
{
    news1_Tex = new QTextEdit(this);
    news2_Tex = new QTextEdit(this);
    news3_Tex = new QTextEdit(this);
    news4_Tex = new QTextEdit(this);
    news5_Tex = new QTextEdit(this);

    bookmarks1_Btn = new QPushButton(this);
    bookmarks2_Btn = new QPushButton(this);
    bookmarks3_Btn = new QPushButton(this);
    bookmarks4_Btn = new QPushButton(this);
    bookmarks5_Btn = new QPushButton(this);

    refresh_Btn = new QPushButton(this);
    returnToTop_Btn = new QPushButton(this);
}

void NewsArticle::initSignalAndSlot()
{

}

void NewsArticle::setThisLayout()
{
    news1_Tex->setGeometry(0, 0, BTN_WIDTH, BTN_HEIGHT);
    news2_Tex->setGeometry(0, 1*BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT);
    news3_Tex->setGeometry(0, 2*BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT);
    news4_Tex->setGeometry(0, 3*BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT);
    news5_Tex->setGeometry(0, 4*BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT);

    QGridLayout *thislayout = new QGridLayout();
    thislayout->addWidget(bookmarks1_Btn, 0, 0);
    thislayout->addWidget(bookmarks2_Btn, 1, 0);
    thislayout->addWidget(bookmarks3_Btn, 2, 0);
    thislayout->addWidget(bookmarks4_Btn, 3, 0);
    thislayout->addWidget(bookmarks5_Btn, 4, 0);
    thislayout->addWidget(news1_Tex, 0, 1);
    thislayout->addWidget(news2_Tex, 1, 1);
    thislayout->addWidget(news3_Tex, 2, 1);
    thislayout->addWidget(news4_Tex, 3, 1);
    thislayout->addWidget(news5_Tex, 4, 1);
    thislayout->addWidget(refresh_Btn, 0, 2);
    thislayout->addWidget(returnToTop_Btn, 4, 2);
    setLayout(thislayout);
}

void NewsArticle::setThisStyle()
{
    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome_solid");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    // 创建字体
    QFont font;
    font.setFamily(fontFamilies.at(0));

    bookmarks1_Btn->setToolTip(tr("关闭"));
    bookmarks1_Btn->setFont(font);
    bookmarks1_Btn->setText(QChar(0xf005));
    bookmarks1_Btn->setMaximumSize(30,30);

    bookmarks2_Btn->setToolTip(tr("关闭"));
    bookmarks2_Btn->setFont(font);
    bookmarks2_Btn->setText(QChar(0xf005));
    bookmarks2_Btn->setMaximumSize(30,30);

    bookmarks3_Btn->setToolTip(tr("关闭"));
    bookmarks3_Btn->setFont(font);
    bookmarks3_Btn->setText(QChar(0xf005));
    bookmarks3_Btn->setMaximumSize(30,30);

    bookmarks4_Btn->setToolTip(tr("关闭"));
    bookmarks4_Btn->setFont(font);
    bookmarks4_Btn->setText(QChar(0xf005));
    bookmarks4_Btn->setMaximumSize(30,30);

    bookmarks5_Btn->setToolTip(tr("关闭"));
    bookmarks5_Btn->setFont(font);
    bookmarks5_Btn->setText(QChar(0xf005));
    bookmarks5_Btn->setMaximumSize(30,30);

    refresh_Btn->setToolTip(tr("关闭"));
    refresh_Btn->setFont(font);
    refresh_Btn->setText(QChar(0xf2f9));
    refresh_Btn->setMaximumSize(30,30);

    returnToTop_Btn->setToolTip(tr("关闭"));
    returnToTop_Btn->setFont(font);
    returnToTop_Btn->setText(QChar(0xf062));
    returnToTop_Btn->setMaximumSize(30,30);
}

void NewsArticle::json()//TODO:
{
    // 读取文件内容
    QFile file("./json_test.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text); // 只读文件
    QString value = file.readAll();
    file.close();

    // TODO:错误提示
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);

    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }

    QJsonObject jsonObject = document.object();
    qDebug()<<"jsonObject[name]="<<jsonObject["name"].toString();

    if(jsonObject.contains(QStringLiteral("secondName")))
    {
        QJsonValue jsonValueList = jsonObject.value(QStringLiteral("secondName"));
        QJsonObject item = jsonValueList.toObject();
        qDebug()<<"item[thirdName]="<<item["thirdName"].toString();
    }

    if(jsonObject.contains(QStringLiteral("recoveryPrimaryNode")))
    {
        QJsonValue arrayValue = jsonObject.value(QStringLiteral("recoveryPrimaryNode"));
        if(arrayValue.isArray())
        {
            QJsonArray array = arrayValue.toArray();
            for(int i=0;i<array.size();i++)
            {
                QJsonValue iconArray = array.at(i);
                QJsonObject icon = iconArray.toObject();
                QString id = icon["id"].toString();
                QString iconTxt = icon["iconTxt"].toString();
                QString iconName = icon["iconName"].toString();
                qDebug()<<"id="<<id<<"iconTxt="<<iconTxt<<"iconName="<<iconName;
            }
        }
    }
}
