#include "settingform.h"
#include "ui_settingform.h"

const uint32_t max_columns_a_row = 3;

SettingForm::SettingForm(FM_Setting *s, QWidget *parent) :
    QWidget(parent),
    settings(s),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);
    
}

void SettingForm::updateWebWidget() {
    vector<QString> webList;
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
WebSettingWidget::WebSettingWidget(FM_Setting *s, QString webName, QWidget *parent) : 
    QWidget (parent),
    webName (webName),
    settings(s)
{
    vector<QString> columns;
    vector<bool> columns_states;
    
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
}

void WebSettingWidget::putMeIntoLayout(QVBoxLayout *layout)
{
    layout->addWidget(this->webBtn);
    layout->addWidget(this->columnGroup);
}

void WebSettingWidget::expandColumns()
{
    
}

void WebSettingWidget::contractColumns()
{
    
}
