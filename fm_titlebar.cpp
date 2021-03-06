﻿#include "fm_titlebar.h"
#include "FlyMessage.h"

#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QStyle>
#include <QVBoxLayout>
#include <QFontDatabase>

#define BTN_WIDTH   (40)
#define BTN_HEIGHT  (40)

FM_TitleBar::FM_TitleBar(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground);
    thisparent = (FlyMessage*)parentWidget();// 获得父窗口的指针

    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽

    setThisStyle();// 样式设置
    setThisLayout();// 布局设置

}

FM_TitleBar::~FM_TitleBar()
{
    delete min_Btn; // 显示最大或者最小的图标
    delete max_Btn; // 最大化按钮
    delete close_Btn;// 关闭按钮
    delete settings_Btn;// 设置按钮
    delete connect_Btn;
    delete icon_Lab; // 图标
    delete title_Lab; // 标题
}

void FM_TitleBar::initComponents()
{
    icon_Lab     = new QLabel(this);
    title_Lab    = new QLabel(this);
    Spacer       = new QSpacerItem(100,100,QSizePolicy::Expanding,QSizePolicy::Minimum);
    min_Btn      = new QPushButton(this);
    max_Btn      = new QPushButton(this);
    close_Btn    = new QPushButton(this);
    settings_Btn = new QPushButton(this);
    connect_Btn  = new QPushButton(this);
    titleLayout  = new QHBoxLayout(this);
}

void FM_TitleBar::initSignalAndSlot()
{

}

void FM_TitleBar::setThisLayout()
{
    setFixedHeight(50);
    // 设置控件布局
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(0,0,0,0);
    
    this->setContentsMargins(0,0,0,0);
    
    titleLayout->addWidget(icon_Lab);
    titleLayout->addWidget(title_Lab);
    titleLayout->addItem(Spacer);
    
    titleLayout->addWidget(connect_Btn);
    titleLayout->addWidget(settings_Btn);
    titleLayout->addWidget(min_Btn);
    titleLayout->addWidget(max_Btn);
    titleLayout->addWidget(close_Btn);

    icon_Lab->setMinimumSize(QSize(50,50));
    
    connect_Btn->setMinimumSize(QSize(BTN_WIDTH,BTN_HEIGHT));
    settings_Btn->setMinimumSize(QSize(BTN_WIDTH,BTN_HEIGHT));
    min_Btn->setMinimumSize(QSize(BTN_WIDTH,BTN_HEIGHT));
    max_Btn->setMinimumSize(QSize(BTN_WIDTH,BTN_HEIGHT));
    close_Btn->setMinimumSize(QSize(BTN_WIDTH,BTN_HEIGHT));
}

void FM_TitleBar::setThisStyle()
{
    // 使按钮透明
    close_Btn->setFlat(true);
    min_Btn->setFlat(true);
    max_Btn->setFlat(true);
    settings_Btn->setFlat(true);
    connect_Btn->setFlat(true);

    this->setStyleSheet("FM_TitleBar{background-color: qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                        "stop:0 rgba(255, 255, 255, 160), stop:1 rgba(255, 255, 255, 60));}"
                        "QPushButton{font-size: 12pt; border-style: none; color: black;}"
                        "QPushButton:hover{background-color:lightgray;}"
                        "QPushButton:pressed{background-color:gray; color: lightblue;}");

    close_Btn->setStyleSheet("QPushButton{border-style: none}"
                            "QPushButton:hover{background-color:red; color: black;}"
                            "QPushButton:pressed{background-color:lightred; border-style: inset; }");

    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome_solid");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    // 创建字体
    QFont font;
    font.setFamily(fontFamilies.at(0));

    close_Btn->setToolTip("关闭");
    close_Btn->setFont(font);
    close_Btn->setText(QChar(0xf00d));

    min_Btn->setToolTip("最小化");
    min_Btn->setFont(font);
    min_Btn->setText(QChar(0xf2d1));

    max_Btn->setToolTip("最大化");
    max_Btn->setFont(font);
    max_Btn->setText(QChar(0xf2d0));

    settings_Btn->setToolTip("设置");
    settings_Btn->setFont(font);
    settings_Btn->setText(QChar(0xf0ad));

    connect_Btn->setToolTip("联系我们");
    connect_Btn->setFont(font);
    connect_Btn->setText(QChar(0xf129));

    icon_Lab->setStyleSheet("border-image: url(:/images/logo)");

    title_Lab->setText("飞讯 FlyMessage");
    title_Lab->setStyleSheet("font-size:28px;font-family:\"微软雅黑\"");
}

void FM_TitleBar::mousePressEvent(QMouseEvent *event)
{
    this->thisparent->windowPos = this->thisparent->pos(); // 获得部件当前位置
    this->thisparent->mousePos = event->globalPos(); // 获得鼠标位置
    this->thisparent->dPos = thisparent->mousePos - thisparent->windowPos; // 移动后部件所在的位置
}

void FM_TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    this->thisparent->move(event->globalPos() - this->thisparent->dPos);
}
