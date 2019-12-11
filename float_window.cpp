#include <QWidget>
#include <QFontDatabase>
#include <QStyleOption>
#include <QPainter>

#include "float_window.h"
#include "FlyMessage.h"

FloatWindow::FloatWindow(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽
    setThisLayout();// 布局设置
    setThisStyle();// 样式设置
}

FloatWindow::~FloatWindow()
{

}

void FloatWindow::initComponents()
{
    refresh_Btn = new QPushButton();
    returnToTop_Btn = new QPushButton();
}

void FloatWindow::initSignalAndSlot()
{

}

void FloatWindow::setThisLayout()
{
    refresh_Btn->setFixedSize(QSize(48,48));
    returnToTop_Btn->setFixedSize(QSize(48,48));

    thislayout = new QHBoxLayout();
    thislayout->addWidget(refresh_Btn);
    thislayout->addWidget(returnToTop_Btn);
    this->setLayout(thislayout);
    
    setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
//    setMinimumSize(0, 3);
//    setMaximumSize(16777215, 3);
}

void FloatWindow::setThisStyle()
{
    refresh_Btn->setObjectName("refresh_Btn");
    returnToTop_Btn->setObjectName("returnToTop_Btn");

    setStyleSheet("QPushButton {border: 0px; background: #d9fdff;}"                  
                  "QPushButton:pressed{background: rgb(153,217,234);}"
                  "QPushButton:hover{border:1px solid blue;}"
                  "#refresh_Btn {qproperty-icon: url(:/icons/refresh.ico)}"
                  "#returnToTop_Btn {qproperty-icon: url(:/icons/top.ico)}");

//    // 添加字体文件
//    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome_solid");
//    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
//    // 创建字体
//    QFont font;
//    font.setFamily(fontFamilies.at(0));

    refresh_Btn->setToolTip("刷新");
    returnToTop_Btn->setToolTip("返回顶部");
    
    refresh_Btn->setIconSize(QSize(36,36));
    returnToTop_Btn->setIconSize(QSize(36,36));

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

