#include <QWidget>
#include <QFontDatabase>
#include <QStyleOption>
#include <QPainter>

#include "fm_floatwindow.h"
#include "FlyMessage.h"

FM_FloatWindow::FM_FloatWindow(QWidget *parent) : QWidget(parent)
{
    initComponents();// 初始化组件
    setComponentsLayout();// 布局设置
    setComponentsStyle();// 样式设置
}

FM_FloatWindow::~FM_FloatWindow()
{
    delete refresh_Btn;
    delete returnToTop_Btn;
    delete thislayout;
}

void FM_FloatWindow::initComponents()
{
    refresh_Btn = new QPushButton(this);
    returnToTop_Btn = new QPushButton(this);
}

void FM_FloatWindow::setComponentsLayout()
{
    refresh_Btn->setFixedSize(QSize(36,36));
    returnToTop_Btn->setFixedSize(QSize(36,36));

    thislayout = new QGridLayout(this);
    thislayout->addWidget(refresh_Btn, 0, 0, 1, 1);
    thislayout->addWidget(returnToTop_Btn, 0, 1, 1, 1);
    this->setLayout(thislayout);
    
    setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
}

void FM_FloatWindow::setComponentsStyle()
{
    refresh_Btn->setObjectName("refresh_Btn");
    returnToTop_Btn->setObjectName("returnToTop_Btn");

    setStyleSheet("QPushButton {border-style: none;background: rgba(220,220,220,100);}"
                  "QPushButton:hover{background: rgba(65,105,225,100);}"
                  "#refresh_Btn {qproperty-icon: url(:/icons/refresh.ico)}"
                  "#returnToTop_Btn {qproperty-icon: url(:/icons/top.ico)}");

    refresh_Btn->setToolTip("刷新");
    returnToTop_Btn->setToolTip("返回顶部");
    
    refresh_Btn->setIconSize(QSize(24,24));
    returnToTop_Btn->setIconSize(QSize(24,24));

}

void FM_FloatWindow::hideRefreshBtn()
{
    this->refresh_Btn->hide();
}

void FM_FloatWindow::showRefreshBtn()
{
    this->refresh_Btn->show();
}

void FM_FloatWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

