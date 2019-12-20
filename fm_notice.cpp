#include "fm_notice.h"
#include "fm_json.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QTimerEvent>

FM_Notice::FM_Notice(FM_Setting *s, QWidget *parent):
    settings(s)
{
    timer = new QTimer();
    traySetting(parent);
    set_notice_timer();
}

FM_Notice::~FM_Notice()
{
    delete timer;
    delete trayIcon;
    delete mShowMainAction;
    delete mExitAppAction;
    delete mMenu;
}

void FM_Notice::set_notice_timer()
{
    if(settings->get_global_notice() == true)
    {
        notice_timer = true;
        QTime time = settings->get_refresh_time();
        timer->start(3600000 * time.hour() + 60000 * time.minute()
                     + 1000 * time.second() + time.msec());
    }
    else
    {
        notice_timer = false;
    }
}

void FM_Notice::onInform_notice()
{
    if(notice_timer == false)
    {
        timer->stop();
    }
    else
    {
        QJsonArray array = FM_Json::readJson("./notice.json").array();
        int count = array.size();
        if(count != 0)
        {
            trayIcon->showMessage("飞讯","您有"+QString::number(count)+"条新的通知",
                                  QSystemTrayIcon::Information,1000);
        }
    }
}

void FM_Notice::traySetting(QWidget *parent)
{
    trayIcon = new QSystemTrayIcon(parent);
    trayIcon->setIcon(QIcon(":/images/logo"));
    trayIcon->setToolTip("飞讯"); //提示文字
    createMenu(parent);

    trayIcon->show();
}

void FM_Notice::createMenu(QWidget *parent)
{
    mShowMainAction = new QAction("显示主界面",parent);
    mExitAppAction = new QAction("退出",parent);

    mMenu = new QMenu(parent);
    //新增菜单项---显示主界面
    mMenu->addAction(mShowMainAction);
    //增加分隔符
    mMenu->addSeparator();
    //新增菜单项---退出程序
    mMenu->addAction(mExitAppAction);
    //把QMenu赋给QSystemTrayIcon对象
    trayIcon->setContextMenu(mMenu);
}

void FM_Notice::onMinimize_notice()
{
    trayIcon->showMessage("飞讯","飞讯最小化在任务栏",
                          QSystemTrayIcon::Information,1000);
}
