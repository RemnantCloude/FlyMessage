#include "refresh_window.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLabel>

refresh::refresh(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("刷新设置"));
    setMinimumSize(400, 300);

    initComponents();    // 初始化组件
    initSignalAndSlot(); // 初始化信号与槽

    setThisLayout();
    setThisStyle();
}

refresh::~refresh()
{
}

void refresh::initComponents()
{
    refreshTime_Tex = new QLineEdit();
    time_Lab = new QLabel();

    confirm_Btn = new QPushButton();
    cancel_Btn = new QPushButton();
}

void refresh::initSignalAndSlot()
{
}

void refresh::setThisLayout()
{
    QGridLayout *thislayout = new QGridLayout();
    thislayout->addWidget(refreshTime_Tex, 0, 0);
    thislayout->addWidget(time_Lab, 0, 1);
    thislayout->addWidget(confirm_Btn, 1, 0);
    thislayout->addWidget(cancel_Btn, 1, 1);

    setLayout(thislayout);
}

void refresh::setThisStyle()
{
    refreshTime_Tex->setText(tr("请输入时间"));
    time_Lab->setText(tr("分钟"));

    confirm_Btn->setText(tr("确认"));
    cancel_Btn->setText(tr("取消"));
}
