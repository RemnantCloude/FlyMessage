#include "news.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QGridLayout>
#include <QPalette>
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

News::News(QWidget *parent, QString title, QString time, QString type, QString abstract, bool favor) : QWidget(parent)
{
    isFavor = favor;
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
    favor_Btn = new QPushButton();
    line = new QFrame();
}

void News::initSignalAndSlot()
{
    connect(favor_Btn, SIGNAL(clicked(bool)), this, SLOT(changeFavor(bool)));
}

void News::setThisLayout()
{
    favor_Btn->setFixedSize(QSize(50, 50));

    thislayout = new QGridLayout();
    thislayout->addWidget(title_Lab, 0, 0, 1, 7);
    thislayout->addWidget(favor_Btn, 0, 8, 1, 1);
    thislayout->addWidget(time_Lab, 1, 0, 1, 8);
    thislayout->addWidget(type_Lab, 2, 0, 1, 8);
    thislayout->addWidget(abstract_Lab, 3, 0, 1, 8);

    this->setSizePolicy(QSizePolicy (QSizePolicy::Expanding, QSizePolicy::Preferred));
    this->setLayout(thislayout);
    this->setMinimumSize(400, 0);
}

void News::setThisStyle(QString title, QString time, QString type, QString abstract)
{
    title_Lab->setStyleSheet("QLabel{font-size:22px; font-family:\"黑体\"} color: black;");
    title_Lab->setText(title);
    time_Lab->setText(time);
    type_Lab->setText(type);
    type_Lab->setWordWrap(true);//自动换行
    abstract_Lab->setText(abstract);

    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome_solid");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    // 创建字体
    QFont font;
    font.setFamily(fontFamilies.at(0));

    favor_Btn->setFlat(true);
    favor_Btn->setToolTip("收藏");
    favor_Btn->setFont(font);
    favor_Btn->setText(QChar(0xf005));
    favor_Btn->setStyleSheet("QPushButton{font-size:20px;}");

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

void News::changeFavor(bool)
{
    if(isFavor == true)//删除收藏
    {
        isFavor = false;
        emit FavorNews(DELETENEWS);
        favor_Btn->setStyleSheet("QPushButton{font-size: 20px; color: black}");
    }
    else//添加收藏
    {
        isFavor = true;
        emit FavorNews(ADDNEWS);
        favor_Btn->setStyleSheet("QPushButton{font-size: 20px; color: #00A2FF}");//蓝色
    }
}
