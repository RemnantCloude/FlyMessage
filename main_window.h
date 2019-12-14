#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QScrollArea>
#include <QFile>
#include "news.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {}

    void getNews(QString web);
    void clearNews();

public slots:
    void onRefreshNews();//刷新新闻
    void onFavorNews(bool type);//删除或添加单条收藏夹新闻
    void getFavorNews();//获取收藏夹新闻
    
protected:
    void init();
    void initSignalAndSlot();
    void setThisLayout();
    void setThisStyle();
    
    QJsonObject readJson(QString filename);
    void writeJson(QString filename, QJsonArray news, bool type);
    
    
private:
    QVBoxLayout *thislayout;
    QString website;//当前网站
    int news_amounts;//每个板块新闻显示数量
    QFile favor_json;//收藏夹文件

};

#endif // MAIN_WINDOW_H
