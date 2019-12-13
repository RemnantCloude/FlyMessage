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

void FM_Setting::get_web_list(vector<QString> &ret)
{
    ret.clear();
    foreach(const FM_WebSetting s , web_settings)
    {
        ret.push_back(s.web_name);
    }
}

void FM_Setting::get_web_columns(QString web, vector<QString> ret)
{
    ret.clear();
    foreach(const FM_WebSetting s, web_settings)
    {
        if(s.web_name == web)
            foreach(const FM_ColumnSetting cs, s.web_columns)
                ret.push_back(cs.column_name);
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

void FM_Setting::writeJson(QString filename, QJsonArray news, bool type)
{

}

void FM_Setting::read_setting_from_json()
{
    //读取设置文件内容
    QJsonObject settings = readJson("./test_settings.json");
    QStringList webs = settings.keys();
    
    
    
    //解析文件
    //QJsonObject settings_type = settings.value(web).toObject();
    //QStringList settings_str = settings_type.keys();//获得板块名
}

void FM_Setting::update_setting_from_json()
{
    
}
