#include "float_window.h"
#include "FlyMessage.h"

#include <QWidget>
#include <QFontDatabase>

FloatWindow::FloatWindow(QWidget *parent) : QWidget(parent)
{
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
    refresh_Btn->setFixedSize(QSize(50,50));
    returnToTop_Btn->setFixedSize(QSize(50,50));

    thislayout = new QHBoxLayout();
    thislayout->addWidget(refresh_Btn);
    thislayout->addWidget(returnToTop_Btn);
    this->setLayout(thislayout);
}

void FloatWindow::setThisStyle()
{
    refresh_Btn->setFlat(true);
    returnToTop_Btn->setFlat(true);

    setStyleSheet("QPushButton{font-size: 15pt;}"
                  "QPushButton{color: #43ADFF;}"
                  "QPushButton:pressed{color: blue;}");

    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome_solid");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    // 创建字体
    QFont font;
    font.setFamily(fontFamilies.at(0));

    refresh_Btn->setToolTip("刷新");
    refresh_Btn->setFont(font);
    refresh_Btn->setText(QChar(0xf01e));

    returnToTop_Btn->setToolTip("返回顶部");
    returnToTop_Btn->setFont(font);
    returnToTop_Btn->setText(QChar(0xf062));
}
