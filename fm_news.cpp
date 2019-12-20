#include "fm_news.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QFontDatabase>
#include <QPushButton>

#define ADDNEWS     true
#define DELETENEWS  false

FM_News::FM_News(QWidget *parent, QString title, QString data, QString abstract, QString address, bool needfavor) :
    QWidget(parent),
    address(address)
{
    setAttribute(Qt::WA_StyledBackground,true);
    
    isFavor = !needfavor;
    
    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽

    setThisLayout();
    setThisStyle(title, data, abstract);
}

FM_News::~FM_News()
{
    delete title_Lab;
    delete data_lab;
    delete abstract_Lab;
    delete favor_Btn;
    delete thislayout;
    delete line;
}

void FM_News::initComponents()
{
    title_Lab = new QLabel(this);
    data_lab = new QLabel(this);
    abstract_Lab = new QLabel(this);
    favor_Btn = new QPushButton(this);
    line = new QFrame(this);
}

void FM_News::initSignalAndSlot()
{
    connect(favor_Btn, SIGNAL(clicked(bool)), this, SLOT(changeFavor(bool)));
}

void FM_News::setThisLayout()
{
    favor_Btn->setFixedSize(QSize(50, 50));

    thislayout = new QGridLayout(this);
    thislayout->addWidget(title_Lab, 0, 0, 1, 7);
    thislayout->addWidget(favor_Btn, 0, 8, 1, 1);
    thislayout->addWidget(data_lab, 1, 0, 1, 8);
    thislayout->addWidget(abstract_Lab, 2, 0, 1, 8);

    this->setSizePolicy(QSizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred));
    this->setLayout(thislayout);
    this->setMinimumSize(400, 0);
}

void FM_News::setThisStyle(QString title, QString data, QString abstract)
{
    title_Lab->setStyleSheet("QLabel{font-size:22px; font-family:\"黑体\"} color: black;");
    title_Lab->setText(title);
    data_lab->setText(data);
    abstract_Lab->setWordWrap(true);//自动换行
    abstract_Lab->setText(abstract);

    favor_Btn->setFlat(true);
    if(isFavor)
        favor_Btn->setProperty("favored",true);
    else
        favor_Btn->setProperty("favored",false);

    favor_Btn->setStyleSheet("QPushButton{font-size: 20px; border: 0px; background:rgba(255,255,255,0);}"
                             "QPushButton[favored=false]{qproperty-icon: url(:/icons/star_gray)}"
                             "QPushButton[favored=true]{qproperty-icon: url(:/icons/star_blue)}");
    favor_Btn->setIconSize(QSize(28,28));

    line->setFrameShadow(QFrame::Raised);
    line->setFrameShape(QFrame::HLine);

    line->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
    line->setMinimumSize(0, 3);
    line->setMaximumSize(16777215, 3);
}

void FM_News::mousePressEvent ( QMouseEvent * event ) {
    if(event->button() != Qt::MidButton)
    QDesktopServices::openUrl(
                QUrl(this->address));
    QWidget::mousePressEvent(event);
}

void FM_News::changeFavor(bool)
{
    if(isFavor == true)//删除收藏
    {
        isFavor = false;
        favor_Btn->setProperty("favored",false);
        favor_Btn->style()->unpolish(favor_Btn);
        favor_Btn->style()->polish(favor_Btn);
        emit FavorNews(DELETENEWS);
    }
    else//添加收藏
    {
        isFavor = true;
        favor_Btn->setProperty("favored",true);
        favor_Btn->style()->unpolish(favor_Btn);
        favor_Btn->style()->polish(favor_Btn);
        emit FavorNews(ADDNEWS);
    }
}
