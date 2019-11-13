#include "news_bar.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#define BTN_WIDTH   (80)
#define BTN_HEIGHT  (40)

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
    source1_Btn = new QPushButton(this);
    source2_Btn = new QPushButton(this);
    source3_Btn = new QPushButton(this);
    source4_Btn = new QPushButton(this);
    source5_Btn = new QPushButton(this);
}

void NewsBar::initSignalAndSlot()
{

}

void NewsBar::setThisLayout()
{
    source1_Btn->setGeometry(0, 0, BTN_WIDTH, BTN_HEIGHT);
    source2_Btn->setGeometry(0, 1*BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT);
    source3_Btn->setGeometry(0, 2*BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT);
    source4_Btn->setGeometry(0, 3*BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT);
    source5_Btn->setGeometry(0, 4*BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT);
}

void NewsBar::setThisStyle()
{
    source1_Btn->setFlat(true);
    source2_Btn->setFlat(true);
    source3_Btn->setFlat(true);
    source4_Btn->setFlat(true);
    source5_Btn->setFlat(true);

    setStyleSheet("QPushButton{color: white;}");

    source1_Btn->setText(tr("新闻源1"));
    source2_Btn->setText(tr("新闻源2"));
    source3_Btn->setText(tr("新闻源3"));
    source4_Btn->setText(tr("新闻源4"));
    source5_Btn->setText(tr("新闻源5"));
}
