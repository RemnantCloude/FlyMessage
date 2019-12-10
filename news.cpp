#include "news.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QPalette>
#include <QStyleOption>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>

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
    line = new QFrame(this);
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
    
    this->setSizePolicy(QSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding));
    this->setLayout(thislayout);
    this->setMinimumSize(400, 0);
}

void News::setThisStyle(QString title, QString time, QString type, QString abstract)
{
//    QFile file(":/qss/main_window");
//    file.open(QFile::ReadOnly);
//    QTextStream filetext(&file);
//    QString stylesheet = filetext.readAll();
//    this->setStyleSheet(stylesheet);
//    file.close();
title_Lab->setStyleSheet("QLabel{font-size:22px; font-family:\"黑体\"} color: black;");

title_Lab->setText(title);
title_Lab->setOpenExternalLinks(true);
time_Lab->setText(time);
type_Lab->setText(type);
type_Lab->setWordWrap(true);
abstract_Lab->setText(abstract);

line->setFrameShadow(QFrame::Raised);
line->setFrameShape(QFrame::HLine);

line->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
line->setMinimumSize(0, 3);
line->setMaximumSize(16777215, 3);
}

void News::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

void News::mousePressEvent ( QMouseEvent * event ) {
    if(event->button() != Qt::MidButton)
    QDesktopServices::openUrl(
                QUrl(this->abstract_Lab->text()));
    QWidget::mousePressEvent(event);
}
