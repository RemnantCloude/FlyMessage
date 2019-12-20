#include "fm_json.h"

#include <QMessageBox>

#define ADDNEWS     true
#define DELETENEWS  false
FM_Json::FM_Json(QObject *parent):
    QObject (parent)
{

}

QJsonDocument FM_Json::readJson(QString filename)
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

    return document;
}

void FM_Json::writeJson(QString filename, QJsonObject object)
{
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    file.resize(0);

    QJsonDocument document;
    document.setObject(object);
    file.write(document.toJson());
    file.close();
}

void FM_Json::writeJson(QString filename, QJsonArray news, bool type)
{
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QString value = file.readAll();
    file.resize(0);

    // 错误提示
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
    if (!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug() << "解析json文件错误!";
    }
    QJsonObject jsonObject = document.object();

    //获取新闻
    QJsonArray array = jsonObject.take("favorite").toArray();

    if (type == ADDNEWS) //增加
    {
        array.append(news);
    }
    else //删除
    {
        for (int i = 0; i < array.size(); i++)
        {
            if (array.at(i).toArray() == news)
            {
                array.takeAt(i);
                break;
            }
        }
    }
    jsonObject.insert("favorite", array); //添加到对象中
    document.setObject(jsonObject);
    file.write(document.toJson());
    file.close();
}
