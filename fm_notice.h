#ifndef FM_NOTICE_H
#define FM_NOTICE_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

class FM_Notice : public QObject
{
    Q_OBJECT

public:
    FM_Notice(QWidget *parent,QTime time);
    ~FM_Notice();

    friend class FlyMessage;

    void set_notice_timer(QTime time);

public slots:
    void onMinimize_notice();
    void onInform_notice();

private:
    void initSignalAndSlot();
    void traySetting(QWidget *parent);
    void createMenu(QWidget *parent);

    QTimer* timer;
    QSystemTrayIcon *trayIcon;
    QMenu *mMenu;
    QAction *mShowMainAction;
    QAction *mExitAppAction;
};

#endif // FM_NOTICE_H
