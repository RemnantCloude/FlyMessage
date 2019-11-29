#include "bookmarks_window.h"

#include <QtWidgets/QTextEdit>
#include <QtWidgets/QGridLayout>
#include <QFontDatabase>

#define TEX_WIDTH (500)
#define TEX_HEIGHT (100)

bookmarks::bookmarks(QWidget *parent) : QWidget(parent)
{
    initComponents();    // 初始化组件
    initSignalAndSlot(); // 初始化信号与槽

    setThisLayout();
    setThisStyle();

    
}

bookmarks::~bookmarks()
{

}

void bookmarks::initComponents()
{
    webpage1_Tex = new QTextEdit(this);
    webpage2_Tex = new QTextEdit(this);

    delete1_Btn = new QPushButton(this);
    delete2_Btn = new QPushButton(this);
}

void bookmarks::initSignalAndSlot()
{

}

void bookmarks::setThisLayout()
{
    webpage1_Tex->setGeometry(10, 0, TEX_WIDTH, TEX_HEIGHT);
    webpage2_Tex->setGeometry(10, 1 * TEX_HEIGHT, TEX_WIDTH, TEX_HEIGHT);

    QGridLayout *thislayout = new QGridLayout();
    thislayout->addWidget(webpage1_Tex, 0, 0);
    thislayout->addWidget(webpage2_Tex, 1, 0);
    thislayout->addWidget(delete1_Btn, 0, 1);
    thislayout->addWidget(delete2_Btn, 1, 1);

    setLayout(thislayout);
}

void bookmarks::setThisStyle()
{
    //TEST
    setWindowTitle(tr("收藏夹"));
    webpage1_Tex->setText(tr("网址1"));
    webpage2_Tex->setText(tr("网址2"));

    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome_solid");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    // 创建字体
    QFont font;
    font.setFamily(fontFamilies.at(0));

    delete1_Btn->setToolTip(tr("关闭"));
    delete1_Btn->setFont(font);
    delete1_Btn->setText(QChar(0xf1f8));
    delete1_Btn->setMaximumSize(30, 30);

    delete2_Btn->setToolTip(tr("关闭"));
    delete2_Btn->setFont(font);
    delete2_Btn->setText(QChar(0xf1f8));
    delete2_Btn->setMaximumSize(30, 30);
}
