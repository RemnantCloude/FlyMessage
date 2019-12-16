#include "fm_setting.h"
#include "json.h"

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

void FM_Setting::set_refresh_time(QTime q)
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

bool FM_Setting::is_minimize_notice_first_time()
{
    return this->minimize_notice_first_time;
}

void FM_Setting::set_minimize_notice_first_time()
{
    this->minimize_notice_first_time = false;
}

void FM_Setting::get_web_list(QVector<QString> &ret)
{
    ret.clear();
    foreach(FM_WebSetting *s , web_settings)
    {
        ret.push_back(s->web_name);
    }
}

bool FM_Setting::is_picture_background()
{
    return this->picture_background;
}

void FM_Setting::set_picture_background(bool set)
{
    this->picture_background = set;
    this->update_setting_to_json();
}

QString FM_Setting::get_picture_address()
{
    return this->picture_address;
}

void FM_Setting::set_picture_address(QString address)
{
    this->picture_address = address;
    this->update_setting_to_json();
}

void FM_Setting::get_valid_web(QVector<QString> &ret)
{
    ret.clear();
    foreach(FM_WebSetting* s, web_settings)
    {
        foreach(const FM_ColumnSetting* cs, s->web_columns)
        {
            if(cs->is_enabled)
            {
                ret.append(s->web_name);
                break;
            }
        }
    }
}

void FM_Setting::get_web_columns(QString web, QVector<QString> &ret, QVector<bool> &bret)
{
    ret.clear();
    bret.clear();
    foreach(FM_WebSetting* s, web_settings)
    {
        if(s->web_name == web)
        {
            foreach(const FM_ColumnSetting* cs, s->web_columns)
            {
                ret.push_back(cs->column_name);
                bret.push_back(cs->is_enabled);
            }
            break;
        }
    }
}

bool FM_Setting::get_column_state(QString web, QString column)
{
    foreach(FM_WebSetting *s, web_settings)
    {
        if(s->web_name == web)
        {
            foreach(const FM_ColumnSetting *cs, s->web_columns)
            {
                if(cs->column_name == column)
                {
                    return cs->is_enabled;
                }
            }
        }
    }
    return false;
}

void FM_Setting::set_column_state(QString web, QString column, bool state)
{
    foreach(FM_WebSetting *s, web_settings)
    {
        if(s->web_name == web)
            foreach(FM_ColumnSetting *cs, s->web_columns)
                if(cs->column_name == column)
                {
                    cs->is_enabled = state;
                    break;
                }
    }
}

FM_Setting::FM_Setting()
{
    read_setting_from_json();
}

FM_Setting::~FM_Setting()
{
    foreach(FM_WebSetting * fws, web_settings)
        delete fws;
}

void FM_Setting::read_setting_from_json()
{
    //读取设置文件内容
    QJsonObject settings = FM_Json::readJson("./settings.json").object();
    //读取全局设置
    QJsonObject global_settings = settings.value("global_settings").toObject();

    global_notice = global_settings.value("global_notice").toBool();
    self_starting = global_settings.value("self_starting").toBool();
    minimize_notice_first_time = global_settings.value("minimize_notice_first_time").toBool();
    refresh_time.setHMS(global_settings.value("refresh_time_hour").toInt(),
                        global_settings.value("refresh_time_minute").toInt(),
                        global_settings.value("refresh_time_second").toInt(),
                        global_settings.value("refresh_time_msec").toInt());
    max_display_news = global_settings.value("max_display_news").toInt();
    picture_background = global_settings.value("picture_background").toBool();
    picture_address = global_settings.value("picture_address").toString();
    //读取网站设置
    foreach(const QString &website, settings.keys())
    {
        if(website == "global_settings")
            continue;
        QJsonObject jcolumn = settings.value(website).toObject();
        QVector<FM_ColumnSetting *> column_setting;
        foreach(const QString &column, jcolumn.keys())
        {
            column_setting.append(new FM_ColumnSetting(column, jcolumn.value(column).toBool()));
        }
        web_settings.append(new FM_WebSetting(website, column_setting));
    }
}

void FM_Setting::update_setting_to_json()
{
    QJsonObject settings;

    QJsonObject global_settings;
    global_settings.insert("global_notice", QJsonValue(global_notice));
    global_settings.insert("self_starting", QJsonValue(self_starting));
    global_settings.insert("refresh_time_hour", QJsonValue(refresh_time.hour()));
    global_settings.insert("refresh_time_minute", QJsonValue(refresh_time.minute()));
    global_settings.insert("refresh_time_second", QJsonValue(refresh_time.second()));
    global_settings.insert("refresh_time_msec", QJsonValue(refresh_time.msec()));
    global_settings.insert("max_display_news", QJsonValue(max_display_news));
    global_settings.insert("minimize_notice_first_time", QJsonValue(minimize_notice_first_time));
    global_settings.insert("use_software_first_time", QJsonValue(false));//TODO
    global_settings.insert("picture_background", QJsonValue(picture_background));
    global_settings.insert("picture_address", QJsonValue(picture_address));

    settings.insert("global_settings", global_settings);

    foreach(FM_WebSetting* website, web_settings)
    {
        QJsonObject jcolumn;
        foreach(FM_ColumnSetting* column, website->web_columns)
        {
            jcolumn.insert(column->column_name,
                           QJsonValue(column->is_enabled));
        }
        settings.insert(website->web_name, jcolumn);
    }

    FM_Json::writeJson("./settings.json", settings);
}

FM_WebSetting::~FM_WebSetting()
{
    foreach(FM_ColumnSetting *fcs, web_columns)
        delete fcs;
}
