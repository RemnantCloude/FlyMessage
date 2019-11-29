#include "settings_window.h"
#include "keyword_window.h"
#include "source_window.h"
#include "refresh_window.h"
#include "inform_window.h"

#include <QPushButton>
#include <QGridLayout>

#define BTN_WIDTH (150)
#define BTN_HEIGHT (100)

settings::settings(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("设置"));

    initComponents();    // 初始化组件
    initSignalAndSlot(); // 初始化信号与槽

    setThisLayout();
    setThisStyle();
}

settings::~settings()
{

}

void settings::initComponents()
{
    keywordSettings_Btn = new QPushButton(this);
    sourceSettings_Btn  = new QPushButton(this);
    refreshSettings_Btn = new QPushButton(this);
    informSettings_Btn  = new QPushButton(this);
}

void settings::initSignalAndSlot()
{
    connect(keywordSettings_Btn, SIGNAL(clicked(bool)), SLOT(openKeyword(bool)));
    connect(sourceSettings_Btn, SIGNAL(clicked(bool)), SLOT(openSource(bool)));
    connect(refreshSettings_Btn, SIGNAL(clicked(bool)), SLOT(openRefresh(bool)));
    connect(informSettings_Btn, SIGNAL(clicked(bool)), SLOT(openInform(bool)));
}

void settings::setThisLayout()
{
    keywordSettings_Btn->setMinimumSize(BTN_WIDTH, BTN_HEIGHT);
    sourceSettings_Btn->setMinimumSize(BTN_WIDTH, BTN_HEIGHT);
    refreshSettings_Btn->setMinimumSize(BTN_WIDTH, BTN_HEIGHT);
    informSettings_Btn->setMinimumSize(BTN_WIDTH, BTN_HEIGHT);

    QGridLayout *thislayout = new QGridLayout();
    thislayout->addWidget(keywordSettings_Btn, 0, 0);
    thislayout->addWidget(sourceSettings_Btn, 0, 1);
    thislayout->addWidget(refreshSettings_Btn, 1, 0);
    thislayout->addWidget(informSettings_Btn, 1, 1);
    setLayout(thislayout);
}

void settings::setThisStyle()
{
    keywordSettings_Btn->setText(tr("关键词设置"));
    sourceSettings_Btn->setText(tr("来源网站设置"));
    refreshSettings_Btn->setText(tr("刷新设置"));
    informSettings_Btn->setText(tr("通知设置"));
}

void settings::openKeyword(bool)
{
    QWidget *keyword_window = new keyword;
    keyword_window->show();
}

void settings::openSource(bool)
{
    QWidget *source_window = new source;
    source_window->show();
}

void settings::openRefresh(bool)
{
    QWidget *refresh_window = new refresh;
    refresh_window->show();
}

void settings::openInform(bool)
{
    QWidget *inform_window = new inform;
    inform_window->show();
}