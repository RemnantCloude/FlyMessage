#ifndef FLY_MESSAGE_H
#define FLY_MESSAGE_H
#include <QScroller>
#include <QWidget>
#include <QScrollArea>
#include <QWidget>
#include <QString>
#include <QStyle>
#include <QGridLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QResizeEvent>

#include "fm_titlebar.h"
#include "fm_sidebar.h"
#include "fm_mainwindow.h"
#include "fm_floatwindow.h"
#include "fm_settingform.h"
#include "fm_notice.h"
#include "fm_waitwidget.h"

class FlyMessage : public QWidget
{
    Q_OBJECT

public:
    explicit FlyMessage(QWidget *parent = nullptr);
    ~FlyMessage();
    // 窗体移动事件的点
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    
private:
    FM_WaitWidget* waitwidget;
    FM_SideBar* sidebar;
    FM_MainWindow* mainwindow;
    FM_TitleBar* titlebar;
    
    FM_FloatWindow *floatwindow;
    FM_SettingForm *settingform;
    
    QThread* backstageThread;
    FM_MainWindowProxy* mainwindowProxy;
    
    QGridLayout *GLay;
    QScrollArea *scrollarea;
    QScroller *scroller;
    
    QImage background; // 背景图片
    
    QVector<FM_SideItemData> main_sidebar_items;
    QVector<FM_SideItemData> setting_sidebar_items;
    
    FM_Setting *settings;
    FM_Notice *notice;
    
signals:
    void minimize_notice();

public slots:
    void onMin(bool);
    void onMax(bool);
    void onClose(bool);
    void returnToTop();
    void returnToTopAtOnce();
    void moveToSettingForm();
    void moveToMainWindow();
    void actSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void setBackgroundImage();

protected:
    void initComponents();
    void initSignalAndSlot();
    void initMainSideBarItems();
    void reinitMainSideBarItems();
    void initSettingSideBarItems();
    
    void setComponentsLayout();
    void setComponentsStyle();

    void resizeEvent(QResizeEvent* size);
    void setAeroStyle();
    void initWindowStyle();
};

#endif // FLY_MESSAGE_H
