#include "fm_sidebar.h"
#include "ui_fm_sidebar.h"
#include <QMessageBox>

FM_SBButton::FM_SBButton(QWidget *parent,const QString &str) :
    QPushButton (parent)
{
    this->setText(str);
    this->setObjectName(str);
    this->setMinimumSize(QSize(0, 50));
}

FM_SideItemData::FM_SideItemData(QString s, void(*f)()) : caption(s), func(f)
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
                  "QPushButton{border: 0px;background-color: rgb(243,243,243);font-size:17px;font-family:\"幼圆\"}"
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
        ui->verticalLayout->insertWidget(1, pButton);
        if(data.func == nullptr) {
            connect(pButton, &FM_SBButton::clicked, this, &FM_SideBar::doNothing);
        }
        else {
            connect(pButton, &FM_SBButton::clicked, this, data.func);
        }
    }
}

void FM_SideBar::doNothing()
{
    //QMessageBox::information(this,"nothing","nothing but everything");
}

void FM_SideBar::clearItems()
{
    foreach (FM_SBButton* btn, items) {   delete btn;  }    
    items.clear();
}

void FM_SideBar::on_pushButton_clicked()
{
    clearItems();
}
