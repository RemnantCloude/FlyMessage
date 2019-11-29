#include "main_window.h"

#include <QWidget>
#include <QString>
#include <QStyle>
#include <QGridLayout>

//TEST:
#include <QDebug>

//TODO:
#define BTN_WIDTH   (40)
#define BTN_HEIGHT  (30)

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
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

MainWindow::~MainWindow()
{

}

//TODO:
void MainWindow::setBackgroundImage(QString filename)
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

void MainWindow::initLayout()
{
    this->resize (1024, 720); // TODO:默认大小需可记忆

    titlebar = new TitleBar(this);
    newsbar = new NewsBar(this);
    newsarticle = new NewsArticle(this);
    centerWidget = new QWidget(this);

    // 设置布局器
    QGridLayout *GLay = new QGridLayout(this);
    GLay->addWidget(titlebar, 0, 0, 1, 5);
    GLay->addWidget(newsbar, 1, 0, 1, 1);
    GLay->addWidget(newsarticle, 1, 1, 1, 4);
    this->setLayout(GLay);
}

void MainWindow::initSignalAndSlot()
{
    connect(titlebar->min_Btn, SIGNAL(clicked(bool)), SLOT(onMin(bool)));
    connect(titlebar->max_Btn, SIGNAL(clicked(bool)), SLOT(onMax(bool)));
    connect(titlebar->close_Btn, SIGNAL(clicked(bool)), SLOT(onClose(bool)));
    connect(titlebar, SIGNAL(mouseDoubleClick(bool)), SLOT(onMax(bool)));
}

void MainWindow::setThisStyle()
{
    
}

void MainWindow::setThisLayout()
{
    // TODO:
    titlebar->setGeometry(0, 0, BTN_HEIGHT + 10, BTN_WIDTH);
}

void MainWindow::onMin(bool)
{
    if( windowState() != Qt::WindowMinimized )
    {
        setWindowState( Qt::WindowMinimized );
    }
}

void MainWindow::onMax(bool)
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

void MainWindow::onClose(bool)
{
    emit close();
}
