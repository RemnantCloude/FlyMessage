#include <QStyleOption>
#include <QPainter>
#include <main_window.h>
#include <QDebug>

#include "fm_sidebar.h"
#include "main_window.h"

FM_SideItemData::FM_SideItemData(QString s, void(FM_SideBar::*f)(), bool cb) : 
    caption(s), checked(cb), func(f)
{
    
}

FM_SBButton::FM_SBButton(QWidget *parent,const QString &str) : QPushButton (parent)
{
    this->setText(str);
    this->setObjectName(str);
    this->setMinimumSize(QSize(0, 50));
    this->setProperty("btnClicked",false);
}

FM_SideBar::FM_SideBar(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground,true);
    setupUI();
}

FM_SideBar::~FM_SideBar()
{
    foreach(FM_SBButton* sbb, items)
        delete sbb;
    delete verticalLayout;
}

void FM_SideBar::setupUI()
{
    verticalLayout = new QVBoxLayout(this);
    vSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    
    resize(200, 373);    
    this->setSizePolicy(QSizePolicy (QSizePolicy::Fixed, QSizePolicy::Preferred));
    this->setMinimumSize(QSize(200, 0));
    
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addItem(vSpacer);
    
    setStyleSheet("QPushButton{border: 0px; font-size:17px;font-family:\"幼圆\";}"
                  "QPushButton[btnClicked=true]{background-color:rgba(200,200,200,100);qproperty-icon: url(:/icons/right.ico);}"
                  "QPushButton[btnClicked=false]{qproperty-icon:none;}"
                  "QPushButton[btnClicked=false]:hover{background-color: rgba(220,220,220,100);}"
                  "QPushButton[btnClicked=false]:pressed {background-color: rgba(200,200,200,100);}"
                  );
    
}

void FM_SideBar::setBtnClicked(int cpi)
{
    if(cpi < items.size())
    {
        emit items[cpi]->clicked();
    }
    
}

void FM_SideBar::setSideBarList(QVector<FM_SideItemData> &idata)
{
    clearItems();
    int items_now = verticalLayout->count();
    FM_SBButton *tempBtn = nullptr;
    foreach(FM_SideItemData data, idata) {
        FM_SBButton *pButton;
        pButton = new FM_SBButton(this, data.caption);
        pButton->web_name = data.caption;
        
        if(data.checked == true)
            tempBtn = pButton;
        
        this->items.append(pButton);
        verticalLayout->insertWidget(items_now-1, pButton);
        items_now++;
        
        connect(pButton, &FM_SBButton::clicked, this, &FM_SideBar::defaultAction);
        connect(pButton, &FM_SBButton::clicked, this, data.func);
    }
    btn_data = &idata;
    if(tempBtn != nullptr)
        emit tempBtn->clicked();
}

void FM_SideBar::addSideBarList(QVector<FM_SideItemData> &idata, FM_SideItemData &data)
{
    int items_now = verticalLayout->count();
    FM_SBButton *pButton;
    pButton = new FM_SBButton(this, data.caption);
    pButton->web_name = data.caption;
    
    this->items.append(pButton);
    verticalLayout->insertWidget(items_now-1, pButton);
    items_now++;
    
    connect(pButton, &FM_SBButton::clicked, this, &FM_SideBar::defaultAction);
    connect(pButton, &FM_SBButton::clicked, this, data.func);
    
    idata.append(data);
}

void FM_SideBar::defaultAction()
{
    FM_SBButton *selected = qobject_cast<FM_SBButton *>(QObject::sender());

    for (int i = 0; i < items.size(); ++i)
    {
        if(items[i]!=selected)
        {
            items[i]->setProperty("btnClicked", false);
            (*btn_data)[i].checked = false;
        }
        else
        {
            items[i]->setProperty("btnClicked", true);
            (*btn_data)[i].checked = true;
        }

        items[i]->style()->unpolish(items[i]);
        items[i]->style()->polish(items[i]);
    }
}

/**
  * @brief: 收藏
  * */
void FM_SideBar::customAction_favor()
{
    emit signal_favor();
}

/**
  * @brief: 返回主界面
  * */
void FM_SideBar::customAction_back()
{
    emit signal_back();
}

/**
  * @brief: 获取指定栏目
  * */
void FM_SideBar::customAction_column()
{
    FM_SBButton *sender = qobject_cast<FM_SBButton *>(QObject::sender());
    emit signal_refresh(sender->web_name);
}

void FM_SideBar::clearItems()
{
    foreach (FM_SBButton* btn, items) {   delete btn;  }    
    items.clear();
}
