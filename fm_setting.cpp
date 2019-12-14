#include "fm_setting.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QDebug>

bool FM_Setting::get_global_notice()
{
    return this->global_notice;
}

void FM_Setting::set_global_notice(bool b)
{
    this->global_notice = b;
}

QTime FM_Setting::get_refresh_time()
{
    return this->refresh_time;
}

void FM_Setting::set_refresh_time(QTime &q)
{
    this->refresh_time = q;
}

int FM_Setting::get_max_display_news()
{
    return this->max_display_news;
}

void FM_Setting::set_max_display_news(int i)
{
    this->max_display_news = i;
}

void FM_Setting::get_web_list(QVector<QString> &ret)
{
    ret.clear();
    foreach(const FM_WebSetting s , web_settings)
    {
        ret.push_back(s.web_name);
    }
}

void FM_Setting::get_web_columns(QString web, QVector<QString> ret, vector<bool> bret)
{
    ret.clear();
    bret.clear();
    foreach(const FM_WebSetting s, web_settings)
    {
        if(s.web_name == web)
            foreach(const FM_ColumnSetting cs, s.web_columns)
            {
                ret.push_back(cs.column_name);
                bret.push_back(cs.is_enabled);
            }
        break;
    }
}

bool FM_Setting::get_column_state(QString web, QString column)
{
    foreach(const FM_WebSetting s, web_settings)
    {
        if(s.web_name == web)
            foreach(const FM_ColumnSetting cs, s.web_columns)
                if(cs.column_name == column)
                    return cs.is_enabled;
        break;
    }
                
}


QJsonObject FM_Setting::readJson(QString filename)
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

void FM_Setting::writeJson(QString filename, QJsonObject settings)
{
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    file.resize(0);

    QJsonDocument document;
    document.setObject(settings);
    file.write(document.toJson());
    file.close();
}

void FM_Setting::read_setting_from_json()
{
    //读取设置文件内容
    QJsonObject settings = readJson("./test_settings.json");
    QJsonObject global_settings = settings.value("global_settings").toObject();

    global_notice = global_settings.value("global_notice").toBool();
    refresh_time.setHMS(global_settings.value("refresh_time_hour").toInt(),
                        global_settings.value("refresh_time_minute").toInt(),
                        global_settings.value("refresh_time_second").toInt(),
                        global_settings.value("refresh_time_msec").toInt());
    max_display_news = global_settings.value("max_display_news").toInt();

    foreach(const QString &website, settings.keys())
    {
        QJsonObject jcolumn = settings.value(website).toObject();
        QVector<FM_ColumnSetting> column_setting;
        foreach(const QString &column, jcolumn.keys())
        {
            column_setting.append(column, jcolumn.value(column));
        }
        web_settings.append(website, )
    }
}

void FM_Setting::update_setting_from_json()
{
    QJsonObject settings;
    settings.insert("global_notice", QJsonValue(global_notice));
    settings.insert("refresh_time_hour", QJsonValue(refresh_time.hour()));
    settings.insert("refresh_time_minute", QJsonValue(refresh_time.minute()));
    settings.insert("refresh_time_second", QJsonValue(refresh_time.second()));
    settings.insert("refresh_time_msec", QJsonValue(refresh_time.msec()));
    settings.insert("max_display_news", QJsonValue(max_display_news));
    settings.insert("minimize_notice_first_time", QJsonValue(false));
    settings.insert("use_software_first_time", QJsonValue(false));

    writeJson("./test_settings.json", settings);
}
