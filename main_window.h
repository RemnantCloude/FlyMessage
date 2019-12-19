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
    void writeFavor(QString title, QString data, QString abstract, QString address, bool type);
public slots:
    void onRefreshNews();
    void onRefreshNews(QString website);//刷新新闻
    void onFavorNews(bool type);//删除或添加单条收藏夹新闻
    void addNewsItem(QString title, QString data, QString abstract, QString address, bool needFavor);
    void stopPaint();
    void startPaint();
protected:
    void init();
    void initSignalAndSlot();
    void setThisLayout();
    void setThisStyle();

    void refreshAllNews();
    
    void paintEvent(QPaintEvent *event);
private:
    QVBoxLayout *thislayout;
    QString now_website;
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
