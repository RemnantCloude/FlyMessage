#include <QWidget>
#include <QFontDatabase>
#include <QStyleOption>
#include <QPainter>

#include "float_window.h"
#include "FlyMessage.h"

FloatWindow::FloatWindow(QWidget *parent) : QWidget(parent)
{
    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽
    setThisLayout();// 布局设置
    setThisStyle();// 样式设置
}

FloatWindow::~FloatWindow()
{
    delete refresh_Btn;
    delete returnToTop_Btn;
    delete thislayout;
}

void FloatWindow::initComponents()
{
    refresh_Btn = new QPushButton(this);
    returnToTop_Btn = new QPushButton(this);
}

void FloatWindow::initSignalAndSlot()
{

}

void FloatWindow::setThisLayout()
{
    refresh_Btn->setFixedSize(QSize(36,36));
    returnToTop_Btn->setFixedSize(QSize(36,36));

    thislayout = new QGridLayout(this);
    thislayout->addWidget(refresh_Btn, 0, 0, 1, 1);
    thislayout->addWidget(returnToTop_Btn, 0, 1, 1, 1);
    this->setLayout(thislayout);
    
    setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
}

void FloatWindow::setThisStyle()
{
    refresh_Btn->setObjectName("refresh_Btn");
    returnToTop_Btn->setObjectName("returnToTop_Btn");

    setStyleSheet("QPushButton {border: 1px solid blue;border-radius:5px; background: rgba(255,255,255,100);}"
                  "QPushButton:hover{background: rgb(220,220,220);}"
                  "#refresh_Btn {qproperty-icon: url(:/icons/refresh.ico)}"
                  "#returnToTop_Btn {qproperty-icon: url(:/icons/top.ico)}");

    refresh_Btn->setToolTip("刷新");
    returnToTop_Btn->setToolTip("返回顶部");
    
    refresh_Btn->setIconSize(QSize(24,24));
    returnToTop_Btn->setIconSize(QSize(24,24));

}

void FloatWindow::hideRefreshBtn()
{
    this->refresh_Btn->hide();
}

void FloatWindow::showRefreshBtn()
{
    this->refresh_Btn->show();
}

void FloatWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

