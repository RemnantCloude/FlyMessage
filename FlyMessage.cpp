#include "FlyMessage.h"
#include "float_window.h"
#include "main_window.h"
#include "aero.h"

#include <QPainter>
//TODO:
#define BTN_WIDTH   (40)
#define BTN_HEIGHT  (30)

FlyMessage::FlyMessage(QWidget *parent) : 
    QWidget(parent),
    settings(new FM_Setting())
{    
    // 初始化窗体
    initComponents(); 
    
    // 设置控件位置和风格样式
    setComponentsLayout();
    setComponentsStyle();
    //setAeroStyle();
    initWindowStyle();
    
    // 初始化信号与槽
    initSignalAndSlot();
    
    traySetting();   
}

void FlyMessage::initWindowStyle()
{
    this->resize (1024, 720); // TODO:默认大小需可记忆
    this->setStyleSheet("TitleBar{background-color:rgba(255,243,255,60);}"
                        "FM_SideBar{background-color:rgba(255,255,255,60);}");    

    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setWindowFlags(Qt::FramelessWindowHint |Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint); 
    setAttribute(Qt::WA_TranslucentBackground, true);

    setAeroStyle();
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
    mainwindow = new MainWindow(settings, this);
    scrollarea = new QScrollArea(this);
    floatwindow = new FloatWindow(this);
    settingform = new SettingForm(settings, this);
    GLay = new QGridLayout(this);
    scroller = QScroller::scroller(scrollarea);
    initSideBar();
    settingform->hide();
}

void FlyMessage::initSideBar()
{
    
    main_sidebar_items.append(FM_SideItemData("加载json", &FM_SideBar::customAction_refresh));
    main_sidebar_items.append(FM_SideItemData("收藏夹", &FM_SideBar::customAction_favor));
    
    setting_sidebar_items.append(FM_SideItemData("返回主界面", &FM_SideBar::customAction_back));
    
    connect(sidebar, &FM_SideBar::signal_refresh, mainwindow, &MainWindow::onRefreshNews);
    connect(sidebar, &FM_SideBar::signal_refresh, floatwindow, &FloatWindow::showRefreshBtn);
    
    connect(sidebar, &FM_SideBar::signal_favor, mainwindow, &MainWindow::getFavorNews);
    connect(sidebar, &FM_SideBar::signal_favor, floatwindow, &FloatWindow::hideRefreshBtn);
    
    connect(sidebar, &FM_SideBar::signal_back, this, &FlyMessage::moveToMainWindow);
    connect(sidebar, &FM_SideBar::signal_back, settingform, &SettingForm::updateGlobalSettings);
    
    sidebar->setSideBarList(main_sidebar_items);
}

void FlyMessage::initSignalAndSlot()
{
    connect(titlebar->min_Btn, SIGNAL(clicked(bool)), SLOT(onMin(bool)));
    connect(titlebar->max_Btn, SIGNAL(clicked(bool)), SLOT(onMax(bool)));
    connect(titlebar->close_Btn, SIGNAL(clicked(bool)), SLOT(onClose(bool)));
    connect(titlebar, SIGNAL(mouseDoubleClick(bool)), SLOT(onMax(bool)));
    connect(titlebar->settings_Btn, SIGNAL(clicked()), SLOT(moveToSettingForm()));
    
    connect(floatwindow->refresh_Btn, SIGNAL(clicked()), mainwindow, SLOT(onRefreshNews()));
    connect(floatwindow->returnToTop_Btn, SIGNAL(clicked()), this, SLOT(returnToTop()));
}

void FlyMessage::setComponentsStyle()
{
    
    scrollarea->setWidgetResizable(true);
    scrollarea->setStyleSheet("QScrollArea {background:white}");
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    settingform->setStyleSheet("SettingForm{background:white;}");
    
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
    Q_UNUSED(size);
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
    sidebar->setSideBarList(setting_sidebar_items);
}

void FlyMessage::moveToMainWindow()
{
    scrollarea->takeWidget();
    scrollarea->setWidget(mainwindow);
    floatwindow->show();
    settingform->hide();
    setting_sidebar_items[0].checked = false;
    sidebar->setSideBarList(main_sidebar_items);
}

void FlyMessage::setAeroStyle()
{

    HWND hwnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_EX_LAYERED);
    
    HMODULE hUser = GetModuleHandle(L"user32.dll");
    if (hUser)
    {
        pfnSetWindowCompositionAttribute setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
        if (setWindowCompositionAttribute)
        {
            ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
            WINDOWCOMPOSITIONATTRIBDATA data;
            data.Attrib = WCA_ACCENT_POLICY;
            data.pvData = &accent;
            data.cbData = sizeof(accent);
            setWindowCompositionAttribute(hwnd, &data);
        }
    }
}
