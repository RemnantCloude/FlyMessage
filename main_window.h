#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>

#include "title_bar.h"
#include "news_bar.h"
#include "news_article.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool hasBackgroundImage;

    TitleBar* titlebar;
    NewsBar* newsbar;
    NewsArticle* newsarticle;//TODO:
    QWidget* centerWidget;
    
    QImage background; // 背景图片

    // 窗体移动事件的点
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;

public slots:
    void onMin(bool);
    void onMax(bool);
    void onClose(bool);

private:

protected:
    void initLayout();
    void initSignalAndSlot();

    void setThisLayout();
    void setThisStyle();
    void setBackgroundImage(QString filename); // 设置背景图片

};

#endif // MAIN_WINDOW_H
