
#ifndef FM_SIDEBAR_H
#define FM_SIDEBAR_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
namespace Ui {
class FM_SideBar;
}

class FM_SideBar;

class FM_SBButton : public QPushButton {
    Q_OBJECT
public:
    explicit FM_SBButton(QWidget *parent,const QString &str);
    
    ~FM_SBButton() {}
};

struct FM_SideItemData {
    FM_SideItemData() {}
    FM_SideItemData(QString s, void(FM_SideBar::*f)());
    ~FM_SideItemData() {}
    QString caption;
    void (FM_SideBar::*func)();
    
};

class FM_SideBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit FM_SideBar(QWidget *parent = nullptr);
    ~FM_SideBar();
    void setSideBarList(QVector<FM_SideItemData> &idata);
    void setWidgetStyle();
    void clearItems();
    
public slots:
    void defaultAction();
    void customAction_refresh();
    void customAction_favor();
signals:
    void signal_refresh(QString);
    void signal_favor(void);
private:
    Ui::FM_SideBar *ui;
    QVector<FM_SBButton*> items;
};

#endif // FM_SIDEBAR_H
