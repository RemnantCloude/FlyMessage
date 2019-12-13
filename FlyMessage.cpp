#include "FlyMessage.h"
#include "float_window.h"
#include "main_window.h"

//TODO:
#define BTN_WIDTH   (40)
#define BTN_HEIGHT  (30)

FlyMessage::FlyMessage(QWidget *parent) : QWidget(parent)
{
    // 无边框化|添加任务栏右键菜单|添加最大化最小化按键
    this->setWindowFlags(Qt::FramelessWindowHint |Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint); 
    this->resize (1024, 720); // TODO:默认大小需可记忆
    // hasBackgroundImage = false; // 默认无背景图片
    // setBackgroundImage(":/images/bg");
    
    // 初始化窗体
    initComponents(); 
    
    // 设置控件位置和风格样式
    setComponentsLayout();
    setComponentsStyle();
    
    // 初始化信号与槽
    initSignalAndSlot();
    
    traySetting();
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

void FlyMessage::initComponents()
{
    titlebar = new TitleBar(this);
    sidebar = new FM_SideBar(this);
    mainwindow = new MainWindow(this);
    scrollarea = new QScrollArea(this);
    floatwindow = new FloatWindow(this);
    settingform = new SettingForm(this);
    GLay = new QGridLayout(this);
    scroller = QScroller::scroller(scrollarea);
    initSideBar();
    settingform->hide();
}

void FlyMessage::initSideBar()
{
    QVector<FM_SideItemData> items;
    items.append(FM_SideItemData("加载json", &FM_SideBar::customAction_refresh));
    items.append(FM_SideItemData("收藏夹", &FM_SideBar::customAction_favor));
    sidebar->setSideBarList(items);
    
    connect(sidebar, &FM_SideBar::signal_refresh, mainwindow, &MainWindow::getNews);
    connect(sidebar, &FM_SideBar::signal_refresh, floatwindow, &FloatWindow::showRefreshBtn);
    connect(sidebar, &FM_SideBar::signal_favor, mainwindow, &MainWindow::getFavorNews);
    connect(sidebar, &FM_SideBar::signal_favor, floatwindow, &FloatWindow::hideRefreshBtn);
}

void FlyMessage::initSignalAndSlot()
{
    connect(titlebar->min_Btn, SIGNAL(clicked(bool)), SLOT(onMin(bool)));
    connect(titlebar->max_Btn, SIGNAL(clicked(bool)), SLOT(onMax(bool)));
    connect(titlebar->close_Btn, SIGNAL(clicked(bool)), SLOT(onClose(bool)));
    connect(titlebar, SIGNAL(mouseDoubleClick(bool)), SLOT(onMax(bool)));
    connect(titlebar->settings_Btn, SIGNAL(clicked()), SLOT(moveToSettingForm()));
    
    connect(floatwindow->refresh_Btn, SIGNAL(clicked(bool)), mainwindow, SLOT(onRefreshNews(bool)));
    connect(floatwindow->returnToTop_Btn, SIGNAL(clicked()), this, SLOT(returnToTop()));
}

void FlyMessage::setComponentsStyle()
{
    
    scrollarea->setWidgetResizable(true);
    scrollarea->setStyleSheet("QScrollArea {background:white}");
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    settingform->setStyleSheet("SettingForm{background:white}");
    
    GLay->setContentsMargins(6,6,6,6);
    GLay->setSpacing(0);
}

void FlyMessage::setComponentsLayout()
{
    titlebar->setGeometry(0, 0, BTN_HEIGHT + 10, BTN_WIDTH);

    // 设置布局器
    scrollarea->setWidget(mainwindow);
    scrollarea->setAlignment(Qt::AlignHCenter);

    GLay->addWidget(titlebar, 0, 0, 1, 5);
    GLay->addWidget(sidebar, 1, 0, 1, 1);
    GLay->addWidget(scrollarea, 1, 1, 1, 4);

    this->setLayout(GLay);
}

void FlyMessage::traySetting()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/logo"));
    trayIcon->setToolTip("飞讯"); //提示文字
    createMenu();
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(actSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
}

void FlyMessage::createMenu()
{
    mShowMainAction = new QAction("显示主界面",this);
    connect(mShowMainAction,SIGNAL(triggered()),this,SLOT(show()));

    mExitAppAction = new QAction("退出",this);
    connect(mExitAppAction,SIGNAL(triggered()),this,SLOT(close()));
    
    mMenu = new QMenu(this);
    //新增菜单项---显示主界面
    mMenu->addAction(mShowMainAction);
    //增加分隔符
    mMenu->addSeparator();
    //新增菜单项---退出程序
    mMenu->addAction(mExitAppAction);
    //把QMenu赋给QSystemTrayIcon对象
    trayIcon->setContextMenu(mMenu);
}

void FlyMessage::actSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:  //双击托盘图标
        break;
    case QSystemTrayIcon::DoubleClick:  //双击托盘图标
        this->show();
        break;
    default:
        break;
    }
}

void FlyMessage::onMin(bool)
{
    this->hide();
    trayIcon->showMessage("飞讯","飞讯最小化在任务栏",QSystemTrayIcon::Information,1000);
}

void FlyMessage::onMax(bool)
{
    if( windowState() != Qt::WindowMaximized )// 最大化
        setWindowState( Qt::WindowMaximized );
    else// 还原成原窗口大小
        setWindowState( Qt::WindowNoState );
}

void FlyMessage::onClose(bool)
{
    emit close();
}

void FlyMessage::resizeEvent(QResizeEvent* size){
    floatwindow->setGeometry(width() - 200,height()-80,120,50);
}

void FlyMessage::returnToTop()
{
    scroller->scrollTo(QPointF(0, 0));
}

void FlyMessage::moveToSettingForm()
{
    scrollarea->takeWidget();
    scrollarea->setWidget(settingform);
    mainwindow->hide();
    floatwindow->hide();
    
    QVector<FM_SideItemData> items;
    items.append(FM_SideItemData("返回主界面", &FM_SideBar::customAction_back));
    sidebar->setSideBarList(items);
    
    connect(sidebar, &FM_SideBar::signal_back, this, &FlyMessage::moveToMainWindow);
}

void FlyMessage::moveToMainWindow()
{
    scrollarea->takeWidget();
    scrollarea->setWidget(mainwindow);
    floatwindow->show();
    settingform->hide();
    
    initSideBar();
}
