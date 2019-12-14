
#ifndef FM_SIDEBAR_H
#define FM_SIDEBAR_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
namespace Ui {
class FM_SideBar;
}

class FM_SideBar;

class FM_SBButton : public QPushButton {
    Q_OBJECT
public:
    explicit FM_SBButton(QWidget *parent, const QString &str, bool checked);
    
    ~FM_SBButton() {}
};

struct FM_SideItemData {
    FM_SideItemData() {}
    FM_SideItemData(QString s, void(FM_SideBar::*f)());
    ~FM_SideItemData() {}
    QString caption;
    bool checked = false;
    void (FM_SideBar::*func)();
    
};

class FM_SideBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit FM_SideBar(QWidget *parent = nullptr);
    ~FM_SideBar() {}
    void setSideBarList(QVector<FM_SideItemData> &idata);
    void clearItems();
    
public slots:
    void defaultAction();
    void customAction_refresh();
    void customAction_favor();
    void customAction_back();
    
signals:
    void signal_refresh(QString);
    void signal_favor(void);
    void signal_back();
    
private:
    Ui::FM_SideBar *ui;
    QVector<FM_SBButton*> items;
    QVector<FM_SideItemData> *btn_data;
    QVBoxLayout *verticalLayout;
    QSpacerItem *vSpacer;
    
    void setupUI();
};

#endif // FM_SIDEBAR_H
