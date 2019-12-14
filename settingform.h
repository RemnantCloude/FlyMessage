#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include "fm_setting.h"
#include <QWidget>
#include <QCommandLinkButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QVBoxLayout>

namespace Ui {
class SettingForm;
}

class WebSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WebSettingWidget(FM_Setting *s, QString webName, QWidget *parent = nullptr);
    ~WebSettingWidget() {}
    void putMeIntoLayout(QVBoxLayout *layout);
    void expandColumns();
    void contractColumns();
private:
    QCommandLinkButton *webBtn;
    QGroupBox *columnGroup;
    QGridLayout *columnLayout;
    vector<QCheckBox *> columnCheckBoxes;
    
    const QString webName;
    FM_Setting *settings;
};

class SettingForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit SettingForm(FM_Setting *s, QWidget *parent = nullptr);
    ~SettingForm();
    void updateWebWidget();
private:
    FM_Setting *settings;
    Ui::SettingForm *ui;
    vector<WebSettingWidget *> websWidget;
};

#endif // SETTINGFORM_H
