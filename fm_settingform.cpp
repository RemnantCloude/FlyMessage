#include "fm_settingform.h"
#include "ui_settingform.h"
#include <QFontDatabase>
#include <QStyleOption>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

const uint32_t max_columns_a_row = 3;

FM_SettingForm::FM_SettingForm(FM_Setting *s, QWidget *parent) :
    QWidget(parent),
    settings(s),
    ui(new Ui::SettingForm)
{
    setAttribute(Qt::WA_StyledBackground,true);
    
    ui->setupUi(this);
    
    setStyleSheet("SettingForm{background:rgba(255,255,255,50);}"
                  "*{font-size:14px;font-family:\"微软雅黑\";}");
    int fontId = QFontDatabase::addApplicationFont(":/fonts/type59");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont myFont;
    myFont.setFamily(fontFamilies.at(0));
    myFont.setPixelSize(24);
    ui->tipLabel->setFont(myFont);
    //this->setFont(myFont);
    
    updateWebWidget();
    updateUIWithSettings();
}

void FM_SettingForm::updateWebWidget() {
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

void FM_SettingForm::updateGlobalSettings()
{
    checkRefreshTime();
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

void FM_SettingForm::checkRefreshTime()
{
    if(ui->HourSpin->value() == 0 && ui->MinuteSpin->value() == 0)
    {
        ui->MinuteSpin->setValue(1);
    }
}

void FM_SettingForm::updateUIWithSettings()
{
    QTime time;
    ui->noticeCheckBox->setChecked(settings->get_global_notice());
    time = settings->get_refresh_time();
    ui->HourSpin->setValue(time.hour());
    ui->MinuteSpin->setValue(time.minute());
    ui->maxNewsNum->setValue(settings->get_max_display_news());
    ui->pictureBackground->setChecked(settings->is_picture_background());
    ui->pictureAddress->setText(settings->get_picture_address());
    ui->autoStartCheckBox->setChecked(settings->get_auto_start());
}

FM_SettingForm::~FM_SettingForm()
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
    
    for(int i = 0; i < columns.size(); i++)
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

void FM_SettingForm::on_browse_Btn_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开图片"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
        ui->pictureAddress->setText(fileNames.front());
        settings->set_picture_address(ui->pictureAddress->text());
        emit changeBackground();
    }
    delete fileDialog;
}

void FM_SettingForm::on_pictureBackground_clicked()
{
    settings->set_picture_background(ui->pictureBackground->checkState());
    emit changeBackground();
}

void FM_SettingForm::on_autoStartCheckBox_clicked()
{
    settings->set_auto_start(ui->autoStartCheckBox->checkState());
    emit refreshAutoStart();
}

void FM_SettingForm::on_noticeCheckBox_clicked()
{
    settings->set_global_notice(ui->noticeCheckBox->checkState());
    emit changeNoticeTimer();
}
