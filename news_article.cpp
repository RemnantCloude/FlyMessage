#include "news_article.h"

#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

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
    QSettings settings("./settings.ini", QSettings::IniFormat);
    if(!settings.isWritable())
        qDebug()<<"Cant read settings"<<endl;
    settings.setValue("test/margin", "微软");
    settings.sync();
    settings.beginGroup("test");
    news1_Tex->setText(settings.value("margin").toString());
    settings.endGroup();
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
}

void NewsArticle::setThisStyle()
{

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
