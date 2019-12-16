#include "FlyMessage.h"
#include "float_window.h"
#include "main_window.h"
#include "mainwindowproxy.h"
#include "aero.h"

#include <QPainter>
#include <QDebug>

FlyMessage::FlyMessage(QWidget *parent) : 
    QWidget(parent),
    settings(new FM_Setting())
{    
    // 初始化窗体
    initComponents(); 
    
    // 设置控件位置和风格样式
    setComponentsLayout();
    setComponentsStyle();
    initWindowStyle();
    setBackgroundImage();
    
    // 初始化信号与槽
    initSignalAndSlot();
    
    settingform->hide();
    waitwidget->hide();
}

FlyMessage::~FlyMessage()
{
    delete titlebar;
    delete sidebar;
    delete mainwindow;
    delete floatwindow;
    delete settingform;

    delete scrollarea;
    delete GLay;
    
    delete settings;
    
    if(myfkThread->isRunning())
    {
        myfkThread->exit();                // 结束该线程。
        myfkThread->wait();
    }
}

void FlyMessage::initWindowStyle()
{
    this->resize (1024, 720);
    this->setContentsMargins(0,0,0,0);
    setBackgroundImage();
    this->setStyleSheet("TitleBar{background-color:rgba(255,255,255,60);}"
                        "FM_SideBar{background-color:rgba(255,255,255,60);}");
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setWindowFlags(Qt::FramelessWindowHint |Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint); 

    setAeroStyle();

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


void FlyMessage::setBackgroundImage()
{
    if(settings->is_picture_background() == true && background.load(settings->get_picture_address()))
    {
        QImage alphaChannel(background.size(),QImage::Format_Alpha8);
        alphaChannel.fill(180);
        background.setAlphaChannel(alphaChannel);
        QPalette pal;
        pal.setBrush(QPalette::Window,
                     QBrush(background.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
        setPalette(pal);
    }
    else
    {
        QImage alphaChannel(size(),QImage::Format_Alpha8);
        alphaChannel.fill(0);
        QPalette pal;
        pal.setBrush(QPalette::Window, QBrush(alphaChannel));
        setPalette(pal);
    }
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
    notice = new FM_Notice(this, settings->get_refresh_time());
    waitwidget = new WaitWidget(this);

    myfkProxy = new MainWindowProxy(mainwindow);
    myfkThread  = new QThread(this);
    myfkThread->start();
    myfkProxy->moveToThread(myfkThread);
    
    
    initSideBarSAS();
    initMainSideBarItems();
    initSettingSideBarItems();
    
    connect(floatwindow->refresh_Btn, SIGNAL(clicked()), mainwindow, SLOT(onRefreshNews()));
    connect(floatwindow->refresh_Btn, SIGNAL(clicked()), this, SLOT(returnToTopAtOnce()));
    connect(floatwindow->returnToTop_Btn, SIGNAL(clicked()), this, SLOT(returnToTop()));

    connect(notice->trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(actSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    connect(notice->mShowMainAction,SIGNAL(triggered()),this,SLOT(show()));
    connect(notice->mExitAppAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(this, SIGNAL(minimize_notice()), notice, SLOT(onMinimize_notice()));
    //后台线程与QThread的Start与finish关联
    connect(myfkThread, &QThread::started, myfkProxy, &MainWindowProxy::threadStarted);
    connect(myfkThread, &QThread::finished, myfkProxy, &MainWindowProxy::threadFinished);
    //UI线程的更新信号与后台进程的getNews关联
    connect(mainwindow, &MainWindow::getNews, myfkProxy, &MainWindowProxy::getNews);
    connect(mainwindow, &MainWindow::getFavorNews, myfkProxy, &MainWindowProxy::getFavorNews);
    connect(mainwindow, &MainWindow::writeFavor, myfkProxy, &MainWindowProxy::writeFavor);
    connect(myfkProxy, &MainWindowProxy::addNewsItemToUI, mainwindow, &MainWindow::addNewsItem,Qt::QueuedConnection);
    connect(myfkProxy, &MainWindowProxy::clearNewsinUI, mainwindow, &MainWindow::clearNews);
    connect(myfkProxy, &MainWindowProxy::wait, waitwidget, &WaitWidget::showup);
    connect(myfkProxy, &MainWindowProxy::stopwait, waitwidget, &WaitWidget::fuckoff);
    connect(myfkProxy, &MainWindowProxy::clearNewsinUI, mainwindow, &MainWindow::clearNews);

    connect(settingform, &SettingForm::fkchange, this, &FlyMessage::setBackgroundImage);
}

void FlyMessage::setComponentsStyle()
{
    
    scrollarea->setWidgetResizable(true);
    scrollarea->setStyleSheet("QScrollArea {background:rgba(255,255,255,0)}");
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    GLay->setContentsMargins(0,0,0,0);
    GLay->setSpacing(0);
}

void FlyMessage::setComponentsLayout()
{
    // 设置布局器
    scrollarea->setWidget(mainwindow);
    scrollarea->setAlignment(Qt::AlignHCenter);

    GLay->addWidget(titlebar, 0, 0, 1, 5);
    GLay->addWidget(sidebar, 1, 0, 1, 1);
    GLay->addWidget(scrollarea, 1, 1, 1, 4);

    this->setLayout(GLay);
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
    if(settings->is_minimize_notice_first_time() == true)
    {
        settings->set_minimize_notice_first_time();
        emit minimize_notice();
    }
}

void FlyMessage::onMax(bool)
{
    if( windowState() != Qt::WindowMaximized )// 最大化
    {
        setWindowState( Qt::WindowMaximized );
        titlebar->max_Btn->setText(QChar(0xf2d2));
    }
    else// 还原成原窗口大小
    {
        setWindowState( Qt::WindowNoState );
        titlebar->max_Btn->setText(QChar(0xf2d0));
    }
}

void FlyMessage::onClose(bool)
{
    emit close();
}

void FlyMessage::resizeEvent(QResizeEvent* size){
    Q_UNUSED(size);
    floatwindow->setGeometry(width() - 200,height()-80,120,50);
    waitwidget->setMaximumSize(size->size());
    waitwidget->setMinimumSize(size->size());

    QPalette pal;
    pal.setBrush(QPalette::Window,
                 QBrush(background.scaled(size->size(), Qt::IgnoreAspectRatio,
                                     Qt::SmoothTransformation)));
    setPalette(pal);
}

void FlyMessage::returnToTopAtOnce()
{
    scrollarea->ensureVisible(0,0);
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
    reinitMainSideBarItems();
}

void FlyMessage::initMainSideBarItems()
{
    main_sidebar_items.append(FM_SideItemData("全部新闻", &FM_SideBar::customAction_column,true));
    main_sidebar_items.append(FM_SideItemData("收藏夹", &FM_SideBar::customAction_favor,false));
    
    QVector<QString> valid_webs;
    settings->get_valid_web(valid_webs);
    foreach(QString s, valid_webs)
    {
        main_sidebar_items.append(FM_SideItemData(s, &FM_SideBar::customAction_column,false));
    }

    sidebar->setSideBarList(main_sidebar_items);
}

void FlyMessage::initSettingSideBarItems()
{
    setting_sidebar_items.clear();
    setting_sidebar_items.append(FM_SideItemData("返回主界面", &FM_SideBar::customAction_back,false));
}

void FlyMessage::initSideBarSAS()
{
    connect(sidebar, SIGNAL(signal_refresh(QString)), mainwindow, SLOT(onRefreshNews(QString)));
    connect(sidebar, &FM_SideBar::signal_refresh, floatwindow, &FloatWindow::showRefreshBtn);

    connect(sidebar, &FM_SideBar::signal_back, settingform, &SettingForm::updateGlobalSettings);
    connect(sidebar, &FM_SideBar::signal_back, this, &FlyMessage::moveToMainWindow);
    connect(sidebar, SIGNAL(signal_back()), this, SLOT(returnToTopAtOnce()));

    connect(sidebar, &FM_SideBar::signal_favor, mainwindow, &MainWindow::getFavorNews);
    connect(sidebar, &FM_SideBar::signal_favor, floatwindow, &FloatWindow::hideRefreshBtn);
}

void FlyMessage::initSignalAndSlot()
{
    connect(titlebar->min_Btn, SIGNAL(clicked(bool)), SLOT(onMin(bool)));
    connect(titlebar->max_Btn, SIGNAL(clicked(bool)), SLOT(onMax(bool)));
    connect(titlebar->close_Btn, SIGNAL(clicked(bool)), SLOT(onClose(bool)));
    connect(titlebar->settings_Btn, SIGNAL(clicked()), SLOT(moveToSettingForm()));
    
    connect(floatwindow->refresh_Btn, SIGNAL(clicked()), mainwindow, SLOT(onRefreshNews()));
    connect(floatwindow->refresh_Btn, SIGNAL(clicked()), this, SLOT(returnToTopAtOnce()));
    connect(floatwindow->returnToTop_Btn, SIGNAL(clicked()), this, SLOT(returnToTop()));
}

void FlyMessage::reinitMainSideBarItems()
{
    QString checked_caption;
    bool find_checked = false;
    
    for (int i = 0; i < main_sidebar_items.size(); i++)
    {
        if(main_sidebar_items[i].checked == true)
            checked_caption = main_sidebar_items[i].caption;
    }
    
    for(int i = main_sidebar_items.size() - 1; i > 1; i--)
        main_sidebar_items.pop_back();

    QVector<QString> valid_webs;
    settings->get_valid_web(valid_webs);
    
    foreach(QString s, valid_webs)
    {
        if(checked_caption == s) {
            main_sidebar_items.append(FM_SideItemData(s, &FM_SideBar::customAction_column,true));
            find_checked = true;
        }
        else {
            main_sidebar_items.append(FM_SideItemData(s, &FM_SideBar::customAction_column,false));
        }
    }

    sidebar->setSideBarList(main_sidebar_items);
    
    if(!find_checked)
        sidebar->setBtnClicked(0);
}
