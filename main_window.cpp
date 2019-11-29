#include "main_window.h"

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

#define BTN_WIDTH   (600)
#define BTN_HEIGHT  (100)

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽

    setThisLayout();
    setThisStyle();
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

void MainWindow::json()//TODO:
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
