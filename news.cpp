#include "news.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QPalette>

News::News(QWidget *parent, QString title, QString time, QString abstract) : QWidget(parent)
{
    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽

    setThisLayout();
    setThisStyle(title, time, abstract);
}

News::~News()
{

}

void News::initComponents()
{
    title_Lab = new QLabel();
    time_Lab = new QLabel();
    abstract_Lab = new QLabel();
}

void News::initSignalAndSlot()
{

}

void News::setThisLayout()
{
    thislayout = new QVBoxLayout();
    thislayout->addWidget(title_Lab);
    thislayout->addWidget(time_Lab);
    thislayout->addWidget(abstract_Lab);
    this->setLayout(thislayout);
    this->setMinimumSize(700, 50);
    this->setMaximumSize(700, 200);
}

void News::setThisStyle(QString title, QString time, QString abstract)
{
    title_Lab->setStyleSheet("QLabel{font-size: 15pt; color: blue;}");

    title_Lab->setText(title);
    title_Lab->setOpenExternalLinks(true);
    time_Lab->setText(time);
    abstract_Lab->setText(abstract);

    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}
