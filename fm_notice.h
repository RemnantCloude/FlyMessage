#ifndef FM_NOTICE_H
#define FM_NOTICE_H

#include <QObject>
#include <QTime>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QJsonObject>
#include <QTimer>
#include "fm_setting.h"

class FM_Notice : public QObject
{
    Q_OBJECT

public:
    FM_Notice(FM_Setting *s, QWidget *parent = nullptr);
    ~FM_Notice();

    friend class FlyMessage;
signals:
    void timeout();

public slots:
    void onMinimize_notice();
    void onInform_notice();
    void set_notice_timer();
private:
    void initSignalAndSlot();
    void traySetting(QWidget *parent);
    void createMenu(QWidget *parent);

    QTimer *timer;
    bool notice_timer;
    QSystemTrayIcon *trayIcon;
    QMenu *mMenu;
    QAction *mShowMainAction;
    QAction *mExitAppAction;
    FM_Setting *settings;
};

#endif // FM_NOTICE_H
