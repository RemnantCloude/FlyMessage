#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QScrollArea>
#include <QFile>


#include "news.h"
#include "fm_setting.h"

enum PageState{
    FavorPage,
    OtherPage
};

class MainWindowProxy;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    friend class MainWindowProxy;

    explicit MainWindow(FM_Setting *se, QWidget *parent = nullptr);
    ~MainWindow();

    void clearNews();
signals:
    void getNews(QString web);
    void getFavorNews();
    void writeJson(QString filename, QJsonArray *news, bool type);
    void writeFavor(QString s1, QString s2, QString s3, QString s4, bool type);
public slots:
    void onRefreshNews();
    void onRefreshNews(QString website);//刷新新闻
    void onFavorNews(bool type);//删除或添加单条收藏夹新闻
    void addNewsItem(QString a, QString b, QString c, QString d, bool needFavor);
protected:
    void init();
    void initSignalAndSlot();
    void setThisLayout();
    void setThisStyle();
    
    QJsonObject readJson(QString filename);
    void refreshAllNews();

private:
    QVBoxLayout *thislayout;
    QString now_website;
    int news_amounts;//每个板块新闻显示数量
    QFile favor_json;//收藏夹文件
    QVector<News *> newsArray;
    FM_Setting *settings;
    QLabel *tipLabel, *tip2Label;
    QLabel *sbImage;
    QSpacerItem *newsSpacer;
/*
 * 非255 代表其他页面
 * 255 代表收藏夹
*/
    PageState pageState;
    void nullPageJudge();
    void deleteNews(News *news);
};

#endif // MAIN_WINDOW_H
