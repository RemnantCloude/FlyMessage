﻿#ifndef FM_SETTING_H
#define FM_SETTING_H

#include <QTime>
#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QObject>

using namespace std;

struct FM_ColumnSetting {
    FM_ColumnSetting (QString c, bool i) : column_name(c), is_enabled(i) {}
    FM_ColumnSetting () {}
    QString column_name;
    bool is_enabled;
};

struct FM_WebSetting{
    FM_WebSetting (QString w, QVector<FM_ColumnSetting *> wc) : web_name(w), web_columns(wc) {}
    ~FM_WebSetting ();
    QString web_name;
    QVector<FM_ColumnSetting *> web_columns;
};

class FM_Setting : public QObject
{
    Q_OBJECT

public:
    explicit FM_Setting();
    ~FM_Setting();
    void read_setting_from_json();
    void update_setting_to_json();
    
    bool get_global_notice();
    void set_global_notice(bool b);

    bool get_auto_start();
    void set_auto_start(bool b);
    
    QTime get_refresh_time();
    void set_refresh_time(QTime q);
    
    int get_max_display_news();
    void set_max_display_news(int i);

    bool is_minimize_notice_first_time();
    void set_minimize_notice_first_time();

    bool is_picture_background();
    void set_picture_background(bool);

    QString get_picture_address();
    void set_picture_address(QString address);
    
    void get_web_list(QVector<QString> &ret);
    void get_web_columns(QString web, QVector<QString> &, QVector<bool> &bret);
    bool get_column_state(QString web, QString column);
    void set_column_state(QString web, QString column, bool state);
    void get_valid_web(QVector<QString> &ret);
public slots:
    void onRefreshAutoStart();
private:
    bool global_notice;
    bool auto_start;
    bool minimize_notice_first_time;
    bool picture_background;
    QString picture_address;
    QTime refresh_time;
    int max_display_news;
    QVector<FM_WebSetting *> web_settings;
};

#endif // FM_SETTING_H
