#include "news.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QPalette>
#include <QStyleOption>
#include <QPainter>

News::News(QWidget *parent, QString title, QString time, QString type, QString abstract) : QWidget(parent)
{
    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽

    setThisLayout();
    setThisStyle(title, time, type, abstract);
}

News::~News()
{

}

void News::initComponents()
{
    title_Lab = new QLabel();
    time_Lab = new QLabel();
    type_Lab = new QLabel();
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
    thislayout->addWidget(type_Lab);
    thislayout->addWidget(abstract_Lab);
    
    
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    
    this->setLayout(thislayout);
    this->setMinimumSize(0, 50);
    this->setMaximumSize(16777215, 250);
}

void News::setThisStyle(QString title, QString time, QString type, QString abstract)
{
    title_Lab->setStyleSheet("QLabel{font-size: 15pt; color: black;}");

    title_Lab->setText(title);
//    title_Lab->setOpenExternalLinks(true);
    time_Lab->setText(time);
    type_Lab->setText(type);
    abstract_Lab->setText(abstract);

    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

void News::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

