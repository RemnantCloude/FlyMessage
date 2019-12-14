#ifndef FM_SETTING_H
#define FM_SETTING_H

#include <QTime>
#include <QString>
#include <vector>
#include <QJsonObject>

using namespace std;

struct FM_ColumnSetting {
    QString column_name;
    bool is_enabled;
};

struct FM_WebSetting{
    QString web_name;
    vector<FM_ColumnSetting> web_columns;
};

class FM_Setting
{
public:
    FM_Setting() {}
    void read_setting_from_json();
    void update_setting_from_json();
    
    bool get_global_notice();
    void set_global_notice(bool b);
    
    QTime get_refresh_time();
    void set_refresh_time(QTime &q);
    
    int get_max_display_news();
    void set_max_display_news(int i);
    
    void get_web_list(vector<QString> &ret);
    void get_web_columns(QString web, vector<QString>);
    bool get_column_state(QString web, QString column);
    
private:
    bool global_notice;
    QTime refresh_time;
    int max_display_news;
    vector<FM_WebSetting> web_settings;
    QJsonObject readJson(QString filename);
    void writeJson(QString filename, QJsonArray news, bool type);
};

#endif // FM_SETTING_H
