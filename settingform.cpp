﻿#include "settingform.h"
#include "ui_settingform.h"
#include <QFontDatabase>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>

const uint32_t max_columns_a_row = 2;

SettingForm::SettingForm(FM_Setting *s, QWidget *parent) :
    QWidget(parent),
    settings(s),
    ui(new Ui::SettingForm)
{
    setAttribute(Qt::WA_StyledBackground,true);
    
    int fontId = QFontDatabase::addApplicationFont(":/fonts/type59");
    
    ui->setupUi(this);
    
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont myFont;
    myFont.setFamily(fontFamilies.at(0));
    myFont.setPixelSize(24);
    ui->tipLabel->setFont(myFont);
    //this->setFont(myFont);
    
    updateWebWidget();
    updateUIWithSettings();
}

void SettingForm::updateWebWidget() {
    QVector<QString> webList;
    settings->get_web_list(webList);
    foreach(QString webName, webList)
    {
        WebSettingWidget *pWidget;
        pWidget = new WebSettingWidget(settings, webName, this);
        pWidget->putMeIntoLayout(ui->webSettingLayout);
        websWidget.append(pWidget);
    }
}

void SettingForm::updateGlobalSettings()
{
    settings->set_global_notice(ui->noticeCheckBox->checkState());
    settings->set_refresh_time(QTime(ui->HourSpin->value(),ui->MinuteSpin->value(),0,0));
    settings->set_max_display_news(ui->maxNewsNum->value());
    foreach(WebSettingWidget *wsw,websWidget)
    {
        foreach(QCheckBox *qcb,wsw->columnCheckBoxes)
        {
            settings->set_column_state(wsw->webName, qcb->text(), qcb->checkState());
        }
    }
    settings->update_setting_to_json();
}

void SettingForm::updateUIWithSettings()
{
    QTime time;
    ui->noticeCheckBox->setChecked(settings->get_global_notice());
    time = settings->get_refresh_time();
    ui->HourSpin->setValue(time.hour());
    ui->MinuteSpin->setValue(time.minute());
    ui->maxNewsNum->setValue(settings->get_max_display_news());    
}

SettingForm::~SettingForm()
{
//    foreach(WebSettingWidget * wsw, websWidget)
//        delete wsw;
    delete ui;
}

WebSettingWidget::WebSettingWidget(FM_Setting *s, QString w, QWidget *parent) : 
    QWidget (parent),
    webName (w),
    settings(s)
{
    QVector<QString> columns;
    QVector<bool> columns_states;
    
    webBtn = new QCommandLinkButton(webName, this);
    columnGroup = new QGroupBox(webName, this);
    columnLayout = new QGridLayout(this);
    
    settings->get_web_columns(webName, columns, columns_states);
    
    for(uint32_t i = 0; i < columns.size(); i++)
    {
        QCheckBox *columnCheck;
        
        columnCheck = new QCheckBox(columns[i], this);
        columnCheck->setChecked(columns_states[i]);
        
        columnLayout->addWidget(columnCheck, i / max_columns_a_row, i % max_columns_a_row);
        this->columnCheckBoxes.append(columnCheck);
    }
    columnGroup->setLayout(columnLayout);
    columnGroup->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum));
    animation = new QPropertyAnimation(columnGroup, "maximumHeight", this);  
    
    connect(webBtn, &QCommandLinkButton::clicked, this, &WebSettingWidget::toggleColumns);
}

/**
    QCommandLinkButton *webBtn;
    QGroupBox *columnGroup;
    QGridLayout *columnLayout;
    QPropertyAnimation *animation;
*/

WebSettingWidget::~WebSettingWidget()
{
//    foreach(QCheckBox *qcb, columnCheckBoxes)
//        delete qcb;
//    delete webBtn;
//    delete columnGroup;
//    delete animation;
//    delete columnLayout;
}



void WebSettingWidget::putMeIntoLayout(QVBoxLayout *layout)
{
    layout->insertWidget(1,this->columnGroup);
    layout->insertWidget(1,this->webBtn);
}

void WebSettingWidget::expandColumns()
{
    animation->setDuration(300);
    animation->setStartValue(0);  
    animation->setEndValue(groupHeight);
    isExtend = true;
    animation->start();
}

void WebSettingWidget::contractColumns()
{
    animation->setDuration(300);
    animation->setStartValue(groupHeight);
    animation->setEndValue(0);
    isExtend = false;
    animation->start();
}

void WebSettingWidget::toggleColumns()
{
    if(isExtend)
    {
        contractColumns();
    }
    else
    {
        expandColumns();
    }
}

void WebSettingWidget::paintEvent(QPaintEvent *event)
{
    if(groupHeight == 0) {
        groupHeight = columnGroup->height();
        columnGroup->setMaximumHeight(0);
    }
    QWidget::paintEvent(event);
    
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
