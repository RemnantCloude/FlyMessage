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
#include <QPropertyAnimation>

namespace Ui {
class SettingForm;
}

class WebSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WebSettingWidget(FM_Setting *s, QString webName, QWidget *parent = nullptr);
    ~WebSettingWidget();
    void putMeIntoLayout(QVBoxLayout *layout);
    void expandColumns();
    void contractColumns();
    
    const QString webName;
    QVector<QCheckBox *> columnCheckBoxes;
protected:
    void paintEvent(QPaintEvent *event);
protected slots:
    void toggleColumns();
private:
    bool isExtend = false;
    int groupHeight = 0;
    QCommandLinkButton *webBtn;
    QGroupBox *columnGroup;
    QGridLayout *columnLayout;
    QPropertyAnimation *animation;
    FM_Setting *settings;
};

class SettingForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit SettingForm(FM_Setting *s, QWidget *parent = nullptr);
    ~SettingForm();
    void updateWebWidget();
signals:
    void changeBackground();
    void refreshAutoStart();
public slots:
    void updateGlobalSettings();
    
private slots:
    void on_browse_Btn_clicked();
    void on_pictureBackground_clicked();
    void on_autoStartCheckBox_clicked();

private:
    FM_Setting *settings;
    Ui::SettingForm *ui;
    QVector<WebSettingWidget *> websWidget;
    void updateUIWithSettings();
};

#endif // SETTINGFORM_H
