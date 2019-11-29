#include "news_bar.h"
#include "settings_window.h"
#include "bookmarks_window.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#define BTN_WIDTH   (150)
#define BTN_HEIGHT  (70)

NewsBar::NewsBar(QWidget *parent) : QWidget(parent)
{
    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽

    setThisLayout();
    setThisStyle();
}

NewsBar::~NewsBar()
{

}

void NewsBar::initComponents()
{
    settings_Btn = new QPushButton(this);
    bookmarks_Btn = new QPushButton(this);
}

void NewsBar::initSignalAndSlot()
{
    connect(settings_Btn, SIGNAL(clicked(bool)), SLOT(openSettings(bool)));
    connect(bookmarks_Btn, SIGNAL(clicked(bool)), SLOT(openBookmarks(bool)));
}

void NewsBar::setThisLayout()
{
    settings_Btn->setGeometry(10, 10, BTN_WIDTH, BTN_HEIGHT);
    bookmarks_Btn->setGeometry(10, 1*BTN_HEIGHT + 10, BTN_WIDTH, BTN_HEIGHT);
}

void NewsBar::setThisStyle()
{
//    settings_Btn->setFlat(true);
//    bookmarks_Btn->setFlat(true);

    // setStyleSheet("QPushButton{color: white;}");

    settings_Btn->setText(tr("设置"));
    bookmarks_Btn->setText(tr("收藏夹"));
}

void NewsBar::openSettings(bool)
{
    QWidget *setting_window = new settings;
    setting_window->show();
}

void NewsBar::openBookmarks(bool)
{
    QWidget *bookmark_window = new bookmarks;
    bookmark_window->show();
}
