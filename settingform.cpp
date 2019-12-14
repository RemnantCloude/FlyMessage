#include "settingform.h"
#include "ui_settingform.h"

const uint32_t max_columns_a_row = 2;

SettingForm::SettingForm(FM_Setting *s, QWidget *parent) :
    QWidget(parent),
    settings(s),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);
    updateWebWidget();
}

void SettingForm::updateWebWidget() {
    QVector<QString> webList;
    settings->get_web_list(webList);
    foreach(QString webName, webList)
    {
        WebSettingWidget *pWidget;
        pWidget = new WebSettingWidget(settings, webName, this);
        pWidget->putMeIntoLayout(ui->webSettingLayout);
    }
}

SettingForm::~SettingForm()
{
    delete ui;
}


/*
    QCommandLinkButton *webBtn;
    QGroupBox *columnGroup;
    QGridLayout *columnLayout;
    vector<QLabel *> columnLabels;
    vector<QCheckBox *> columnCheckBoxes;
*/
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
        
        columnCheck = new QCheckBox(columns[i], columnGroup);
        columnCheck->setChecked(columns_states[i]);
        
        columnLayout->addWidget(columnCheck, i / max_columns_a_row, i % max_columns_a_row);
    }
    columnGroup->setLayout(columnLayout);
    columnGroup->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum));
    columnGroup->setMaximumHeight(0);
    animation = new QPropertyAnimation(columnGroup, "maximumHeight");  
    
    connect(webBtn, &QCommandLinkButton::clicked, this, &WebSettingWidget::toggleColumns);
}

void WebSettingWidget::putMeIntoLayout(QVBoxLayout *layout)
{
    layout->insertWidget(1,this->columnGroup);
    layout->insertWidget(1,this->webBtn);
}

void WebSettingWidget::expandColumns()
{
    
}

void WebSettingWidget::contractColumns()
{
    
}

void WebSettingWidget::toggleColumns()
{
    if(isExtend)
    {
        animation->setDuration(300);
        animation->setStartValue(0);  
        animation->setEndValue(100);
    }
    else
    {
        animation->setDuration(300);
        animation->setStartValue(columnGroup->height()+10);
        animation->setEndValue(0);
    }
    animation->start();
    isExtend = !isExtend;
}
