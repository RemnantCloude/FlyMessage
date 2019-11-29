#include "keyword_window.h"

#include <QtWidgets/QCheckBox>
#include <QGridLayout>

keyword::keyword(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("关键词设置"));
    setMinimumSize(400, 300);

    initComponents();    // 初始化组件
    initSignalAndSlot(); // 初始化信号与槽

    setThisLayout();
    setThisStyle();
}

keyword::~keyword()
{
}

void keyword::initComponents()
{
    keyword1_Chk = new QCheckBox();
    keyword2_Chk = new QCheckBox();
    keyword3_Chk = new QCheckBox();
    keyword4_Chk = new QCheckBox();
    keyword5_Chk = new QCheckBox();

    confirm_Btn = new QPushButton();
    cancel_Btn = new QPushButton();
}

void keyword::initSignalAndSlot()
{
}

void keyword::setThisLayout()
{
    QGridLayout *thislayout = new QGridLayout();
    thislayout->addWidget(keyword1_Chk, 0, 0);
    thislayout->addWidget(keyword2_Chk, 0, 1);
    thislayout->addWidget(keyword3_Chk, 0, 2);
    thislayout->addWidget(keyword4_Chk, 1, 0);
    thislayout->addWidget(keyword5_Chk, 1, 1);
    thislayout->addWidget(confirm_Btn, 2, 1);
    thislayout->addWidget(cancel_Btn, 2, 2);
    setLayout(thislayout);
}

void keyword::setThisStyle()
{
    keyword1_Chk->setText(tr("娱乐"));
    keyword2_Chk->setText(tr("体育"));
    keyword3_Chk->setText(tr("财经"));
    keyword4_Chk->setText(tr("军事"));
    keyword5_Chk->setText(tr("金融"));
    confirm_Btn->setText(tr("确认"));
    cancel_Btn->setText(tr("取消"));
}
