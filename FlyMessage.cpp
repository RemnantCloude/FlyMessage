#include "FlyMessage.h"
#include "float_window.h"

#include <QWidget>
#include <QString>
#include <QStyle>
#include <QGridLayout>
#include <QScrollArea>
#include <QResizeEvent>
//TEST:
#include <QDebug>

#include "FlyMessage.h"
#include "main_window.h"

//TODO:
#define BTN_WIDTH   (40)
#define BTN_HEIGHT  (30)

FlyMessage::FlyMessage(QWidget *parent) : QWidget(parent)
{
    // 无边框化|添加任务栏右键菜单|添加最大化最小化按键
    this->setWindowFlags(Qt::FramelessWindowHint |Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    
    initLayout(); // 初始化窗体
    initSignalAndSlot();// 初始化信号与槽

    // 设置控件位置和风格样式
    setThisLayout();
    setThisStyle();

    
    hasBackgroundImage = false; // 默认无背景图片
//    setBackgroundImage(":/images/bg");
}

FlyMessage::~FlyMessage()
{

}

//TODO:
void FlyMessage::setBackgroundImage(QString filename)
{
    hasBackgroundImage = true;

    background.load(filename);
    setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setBrush(QPalette::Window,
                 QBrush(background.scaled(size(), Qt::IgnoreAspectRatio,
                                     Qt::SmoothTransformation)));
    setPalette(pal);
}

void FlyMessage::initLayout()
{
    this->resize (1024, 720); // TODO:默认大小需可记忆

    titlebar = new TitleBar(this);
    sidebar = new FM_SideBar(this);
    mainwindow = new MainWindow(this);
    scrollarea = new QScrollArea(this);

    floatwindow = new FloatWindow(this);
//    floatwindow->raise();//置顶窗口，貌似没用
    floatwindow->setGeometry(width() - 200, height() - 150, 200, 150);// TODO 全屏时会有bug，位置需要重绘

    // 设置布局器
    scrollarea->setWidget(mainwindow);
    scrollarea->setWidgetResizable(true);
    scrollarea->setStyleSheet("QScrollArea {background:white}");
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    QGridLayout *GLay = new QGridLayout(this);
    GLay->addWidget(titlebar, 0, 0, 1, 5);
    GLay->addWidget(sidebar, 1, 0, 1, 1);
    GLay->addWidget(scrollarea, 1, 1, 1, 4);

    QVector<FM_SideItemData> items;
    items.append(FM_SideItemData("加载json",&FM_SideBar::customClicked1));
    connect(sidebar,&FM_SideBar::signal1, mainwindow, &MainWindow::getNews);
    items.append(FM_SideItemData("咕咕",nullptr));
    items.append(FM_SideItemData("喵喵",nullptr));
    items.append(FM_SideItemData("汪汪",nullptr));
    sidebar->setSideBarList(items);
    
    this->setLayout(GLay);
}

void FlyMessage::initSignalAndSlot()
{
    connect(titlebar->min_Btn, SIGNAL(clicked(bool)), SLOT(onMin(bool)));
    connect(titlebar->max_Btn, SIGNAL(clicked(bool)), SLOT(onMax(bool)));
    connect(titlebar->close_Btn, SIGNAL(clicked(bool)), SLOT(onClose(bool)));
    connect(titlebar, SIGNAL(mouseDoubleClick(bool)), SLOT(onMax(bool)));
    connect(floatwindow->refresh_Btn, SIGNAL(clicked(bool)), mainwindow, SLOT(onRefresh(bool)));
}

void FlyMessage::setThisStyle()
{
    
}

void FlyMessage::setThisLayout()
{
    // TODO:
    titlebar->setGeometry(0, 0, BTN_HEIGHT + 10, BTN_WIDTH);
}

void FlyMessage::onMin(bool)
{
    if( windowState() != Qt::WindowMinimized )
    {
        setWindowState( Qt::WindowMinimized );
    }
}

void FlyMessage::onMax(bool)
{
    if( windowState() != Qt::WindowMaximized )// 最大化
    {
        setWindowState( Qt::WindowMaximized );
    }
    else// 还原成原窗口大小
    {
        setWindowState( Qt::WindowNoState );
    }
}

void FlyMessage::onClose(bool)
{
    emit close();
}
