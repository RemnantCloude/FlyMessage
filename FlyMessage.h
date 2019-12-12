#ifndef FLY_MESSAGE_H
#define FLY_MESSAGE_H

#include <QWidget>
#include <QScrollArea>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QString>
#include <QStyle>
#include <QGridLayout>
#include <QScrollArea>
#include <QResizeEvent>
#include <QMenu>

#include "title_bar.h"
#include "fm_sidebar.h"
#include "main_window.h"
#include "float_window.h"

class FlyMessage : public QWidget
{
    Q_OBJECT

public:
    explicit FlyMessage(QWidget *parent = nullptr);
    ~FlyMessage() {}
    // 窗体移动事件的点
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    
private:
    bool hasBackgroundImage;

    QGridLayout *GLay;
    TitleBar* titlebar;
    FM_SideBar* sidebar;
    MainWindow* mainwindow;
    QScrollArea *scrollarea;
    FloatWindow *floatwindow;
    
    QImage background; // 背景图片
    QSystemTrayIcon *trayIcon;
    QMenu *mMenu;
    QAction *mShowMainAction;
    QAction *mExitAppAction;
    
public slots:
    void onMin(bool);
    void onMax(bool);
    void onClose(bool);
    void returnToTop();
    void actSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

protected:
    void initComponents();
    void initSignalAndSlot();
    void initSideBar();
    void traySetting();
    void createMenu();
    
    void setComponentsLayout();
    void setComponentsStyle();
    void setBackgroundImage(QString filename); // 设置背景图片

    void resizeEvent(QResizeEvent* size);
};

#endif // FLY_MESSAGE_H
