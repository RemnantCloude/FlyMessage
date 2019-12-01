#include "side_bar.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#define BTN_WIDTH   (150)
#define BTN_HEIGHT  (70)

SideBar::SideBar(QWidget *parent) : QWidget(parent)
{
    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽

    setThisLayout();
    setThisStyle();
}

SideBar::~SideBar()
{

}

void SideBar::initComponents()
{
    settings_Btn = new QPushButton(this);
    bookmarks_Btn = new QPushButton(this);
}

void SideBar::initSignalAndSlot()
{
    connect(settings_Btn, SIGNAL(clicked(bool)), SLOT(openSettings(bool)));
    connect(bookmarks_Btn, SIGNAL(clicked(bool)), SLOT(openBookmarks(bool)));
}

void SideBar::setThisLayout()
{
    settings_Btn->setGeometry(10, 10, BTN_WIDTH, BTN_HEIGHT);
    bookmarks_Btn->setGeometry(10, 1*BTN_HEIGHT + 10, BTN_WIDTH, BTN_HEIGHT);
}

void SideBar::setThisStyle()
{
    settings_Btn->setText(tr("设置"));
    bookmarks_Btn->setText(tr("收藏"));
}
