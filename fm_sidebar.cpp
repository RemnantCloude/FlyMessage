#include <QStyleOption>
#include <QPainter>
#include <main_window.h>

#include "fm_sidebar.h"
#include "ui_fm_sidebar.h"
#include "main_window.h"

FM_SBButton::FM_SBButton(QWidget *parent,const QString &str) :
    QPushButton (parent)
{
    this->setText(str);
    this->setObjectName(str);
    this->setMinimumSize(QSize(0, 50));
}

FM_SideItemData::FM_SideItemData(QString s, void(FM_SideBar::*f)()) : caption(s), func(f)
{
    
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
    setStyleSheet("*{background-color: rgb(243,243,243);}"
                  "QPushButton{border: 0px; background-color: rgb(243,243,243);font-size:17px;font-family:\"幼圆\"}"
                  "QPushButton:hover {background-color: rgb(220,220,220);}"
                  "QPushButton:pressed {background-color: rgb(200,200,200);}"
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
        connect(pButton, &FM_SBButton::clicked, this, &FM_SideBar::defaultClicked);
        connect(pButton, &FM_SBButton::clicked, this, data.func);
    }
}

void FM_SideBar::defaultClicked()
{
    FM_SBButton *selected = qobject_cast<FM_SBButton *>(QObject::sender());
    selected->setStyleSheet("QPushButton{background-color:rgb(200,200,200);qproperty-icon: url(:/icons/right.ico);}");
    
    foreach(FM_SBButton *btn, items) {
        if(btn!=selected)
            btn->setStyleSheet("QPushButton{background-color:rgb(243,243,243);qproperty-icon:none;}"
                               "QPushButton:hover{background-color: rgb(220,220,220);}");
    }
}

void FM_SideBar::customClicked1()
{
    emit signal1("website1");
}

void FM_SideBar::clearItems()
{
    foreach (FM_SBButton* btn, items) {   delete btn;  }    
    items.clear();
}

void FM_SideBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}
