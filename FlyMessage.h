#ifndef FLY_MESSAGE_H
#define FLY_MESSAGE_H

#include <QWidget>

#include "title_bar.h"
#include "side_bar.h"
#include "main_window.h"

class FlyMessage : public QWidget
{
    Q_OBJECT

public:
    explicit FlyMessage(QWidget *parent = nullptr);
    ~FlyMessage();

    bool hasBackgroundImage;

    TitleBar* titlebar;
    SideBar* sidebar;
    MainWindow* mainwindow;//TODO:
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

#endif // FLY_MESSAGE_H
