#include "inform_window.h"

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

inform::inform(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("通知设置"));
    setMinimumSize(400, 300);

    initComponents();    // 初始化组件
    initSignalAndSlot(); // 初始化信号与槽

    setThisLayout();
    setThisStyle();
}

inform::~inform()
{
}

void inform::initComponents()
{
    source1_Chk = new QCheckBox();
    source2_Chk = new QCheckBox();

    confirm_Btn = new QPushButton();
    cancel_Btn = new QPushButton();
}

void inform::initSignalAndSlot()
{
}

void inform::setThisLayout()
{
    QGridLayout *thislayout = new QGridLayout();
    thislayout->addWidget(source1_Chk, 0, 0, 1, 3);
    thislayout->addWidget(source2_Chk, 1, 0, 1, 3);
    thislayout->addWidget(confirm_Btn, 2, 1);
    thislayout->addWidget(cancel_Btn, 2, 2);
    setLayout(thislayout);
}

void inform::setThisStyle()
{
    source1_Chk->setText(tr("获取通知消息时弹出提示"));
    source2_Chk->setText(tr("资讯推荐"));
    confirm_Btn->setText(tr("确认"));
    cancel_Btn->setText(tr("取消"));
}
