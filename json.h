#ifndef JSON_H
#define JSON_H

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

#include <QDebug>
namespace json{
    QJsonDocument readJson(QString filename);
    void writeJson(QString filename, QJsonObject object);
    void writeJson(QString filename, QJsonArray news, bool type);
}

#endif // JSON_H
