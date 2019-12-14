#include "settingform.h"
#include "ui_settingform.h"
#include <QFontDatabase>
#include <QStyleOption>
#include <QPainter>

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
    columnGroup->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum));
    //columnGroup->setMaximumHeight(0);
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
