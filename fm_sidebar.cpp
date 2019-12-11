#include <QStyleOption>
#include <QPainter>
#include <main_window.h>

#include "fm_sidebar.h"
#include "ui_fm_sidebar.h"
#include "main_window.h"

FM_SideItemData::FM_SideItemData(QString s, void(FM_SideBar::*f)()) : caption(s), func(f)
{
    
}

FM_SBButton::FM_SBButton(QWidget *parent,const QString &str) :
    QPushButton (parent)
{
    this->setText(str);
    this->setObjectName(str);
    this->setMinimumSize(QSize(0, 50));
    this->setProperty("btnClicked",false);
}

FM_SideBar::FM_SideBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FM_SideBar)
{
    ui->setupUi(this);
    setWidgetStyle();

}

FM_SideBar::~FM_SideBar()
{
    delete ui;
}

void FM_SideBar::setWidgetStyle()
{
    setStyleSheet("QPushButton{border: 0px; font-size:17px;font-family:\"幼圆\"}"
                  "QPushButton[btnClicked=true]{background-color:rgb(200,200,200);qproperty-icon: url(:/icons/right.ico);}"
                  "QPushButton[btnClicked=false]{qproperty-icon:none;}"
                  "QPushButton[btnClicked=false]:hover{background-color: rgb(220,220,220);}"
                  "QPushButton[btnClicked=false]:pressed {background-color: rgb(200,200,200);}"
                  );
}

void FM_SideBar::setSideBarList(QVector<FM_SideItemData> &idata)
{
    clearItems();
    foreach(FM_SideItemData data, idata) {
        FM_SBButton *pButton;
        pButton = new FM_SBButton(this, data.caption);
        
        this->items.append(pButton);
        ui->verticalLayout->insertWidget(0, pButton);
        
        connect(pButton, &FM_SBButton::clicked, this, &FM_SideBar::defaultAction);
        connect(pButton, &FM_SBButton::clicked, this, data.func);
    }
}

void FM_SideBar::defaultAction()
{
    FM_SBButton *selected = qobject_cast<FM_SBButton *>(QObject::sender());

    foreach(FM_SBButton *btn, items)
    {
        if(btn!=selected)
            btn->setProperty("btnClicked", false);
        else
            btn->setProperty("btnClicked", true);
        
        btn->style()->unpolish(btn);
        btn->style()->polish(btn);
    }
}
/**
  * @brief: 刷新
  * */
void FM_SideBar::customAction_refresh()
{
    emit signal_refresh("website1");
}

/**
  * @brief: 收藏
  * */
void FM_SideBar::customAction_favor()
{
    emit signal_favor();
}

void FM_SideBar::clearItems()
{
    foreach (FM_SBButton* btn, items) {   delete btn;  }    
    items.clear();
}
