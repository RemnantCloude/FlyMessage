#ifndef JSON_H
#define JSON_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

#include <QDebug>

class FM_Json : public QObject
{
    Q_OBJECT
public:
    explicit FM_Json(QObject *parent);
    ~FM_Json() {}
    static QJsonDocument readJson(QString filename);
    static void writeJson(QString filename, QJsonObject object);
    static void writeJson(QString filename, QJsonArray news, bool type);
};

#endif // JSON_H
