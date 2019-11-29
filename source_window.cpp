#include "source_window.h"

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

source::source(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("来源网站设置"));
    setMinimumSize(400, 300);

    initComponents();    // 初始化组件
    initSignalAndSlot(); // 初始化信号与槽

    setThisLayout();
    setThisStyle();
}

source::~source()
{
}

void source::initComponents()
{
    source1_Chk = new QCheckBox();
    source2_Chk = new QCheckBox();
    source3_Chk = new QCheckBox();
    source4_Chk = new QCheckBox();
    source5_Chk = new QCheckBox();

    confirm_Btn = new QPushButton();
    cancel_Btn = new QPushButton();
}

void source::initSignalAndSlot()
{
}

void source::setThisLayout()
{
    QGridLayout *thislayout = new QGridLayout();
    thislayout->addWidget(source1_Chk, 0, 0);
    thislayout->addWidget(source2_Chk, 0, 1);
    thislayout->addWidget(source3_Chk, 0, 2);
    thislayout->addWidget(source4_Chk, 1, 0);
    thislayout->addWidget(source5_Chk, 1, 1);
    thislayout->addWidget(confirm_Btn, 2, 1);
    thislayout->addWidget(cancel_Btn, 2, 2);
    setLayout(thislayout);
}

void source::setThisStyle()
{
    source1_Chk->setText(tr("人民新闻"));
    source2_Chk->setText(tr("凤凰资讯"));
    source3_Chk->setText(tr("联合早报"));
    source4_Chk->setText(tr("中国日报"));
    source5_Chk->setText(tr("新浪新闻"));
    confirm_Btn->setText(tr("确认"));
    cancel_Btn->setText(tr("取消"));
}
