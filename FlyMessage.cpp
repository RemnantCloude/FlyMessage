#include "FlyMessage.h"
#include "fm_mainwindowproxy.h"
#include "aero.h"

#include <QPainter>
#include <QDebug>

FlyMessage::FlyMessage(QWidget *parent) : 
    QWidget(parent),
    settings(new FM_Setting())
{    
    // 初始化窗体和组件
    initComponents();
    initMainSideBarItems();
    initSettingSideBarItems();

    // 初始化信号与槽
    initSignalAndSlot();
    
    // 设置控件位置和风格样式
    setComponentsLayout();
    setComponentsStyle();
    initWindowStyle();
    setBackgroundImage();
    
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
    
    if(backstageThread->isRunning())
    {
        backstageThread->exit();                // 结束该线程。
        backstageThread->wait();
    }
}

void FlyMessage::initWindowStyle()
{
    this->resize (1024, 720);
    this->setContentsMargins(0,0,0,0);
    setBackgroundImage();
    this->setStyleSheet("FM_TitleBar{background-color:rgba(255,255,255,60);}"
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

void FlyMessage::setComponentsLayout()
{
    // 设置布局
    scrollarea->setWidget(mainwindow);
    scrollarea->setAlignment(Qt::AlignHCenter);

    GLay->addWidget(titlebar, 0, 0, 1, 5);
    GLay->addWidget(sidebar, 1, 0, 1, 1);
    GLay->addWidget(scrollarea, 1, 1, 1, 4);
    GLay->setContentsMargins(0,0,0,0);
    GLay->setSpacing(0);

    this->setLayout(GLay);
}

void FlyMessage::setComponentsStyle()
{
    scrollarea->setWidgetResizable(true);
    scrollarea->setStyleSheet("QScrollArea {background:rgba(255,255,255,0)}");
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void FlyMessage::actSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger:  //单击托盘图标
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
    waitwidget->setGeometry(0,0,this->width(),this->height());
    waitwidget->image->setAlignment(Qt::AlignHCenter);

    QPalette pal;
    pal.setBrush(QPalette::Window,
                 QBrush(background.scaled(size->size(), Qt::KeepAspectRatioByExpanding,
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

void FlyMessage::initComponents()
{
    titlebar = new FM_TitleBar(this);
    sidebar = new FM_SideBar(this);
    scrollarea = new QScrollArea(this);
    floatwindow = new FM_FloatWindow(this);
    settingform = new FM_SettingForm(settings, this);
    GLay = new QGridLayout(this);
    scroller = QScroller::scroller(scrollarea);
    notice = new FM_Notice(settings, this);
    waitwidget = new FM_WaitWidget(this);
    mainwindow = new FM_MainWindow(settings, this);
    mainwindowProxy = new FM_MainWindowProxy(mainwindow);
    backstageThread = new QThread(this);
    backstageThread->start();
    mainwindowProxy->moveToThread(backstageThread);
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

void FlyMessage::initSignalAndSlot()
{
    connect(titlebar->min_Btn, SIGNAL(clicked(bool)), SLOT(onMin(bool)));
    connect(titlebar->max_Btn, SIGNAL(clicked(bool)), SLOT(onMax(bool)));
    connect(titlebar->close_Btn, SIGNAL(clicked(bool)), SLOT(onClose(bool)));
    connect(titlebar->settings_Btn, SIGNAL(clicked()), SLOT(moveToSettingForm()));
    
    connect(floatwindow->refresh_Btn, SIGNAL(clicked()), this, SLOT(returnToTopAtOnce()));
    connect(floatwindow->returnToTop_Btn, SIGNAL(clicked()), this, SLOT(returnToTop()));

    //新闻爬虫调用
    connect(floatwindow->refresh_Btn, SIGNAL(clicked()), mainwindowProxy, SLOT(startNewsCrawler()));
    connect(mainwindowProxy, SIGNAL(pythonEnd()), mainwindow, SLOT(onRefreshNews()));
    //通知爬虫调用
    connect(notice->timer, SIGNAL(timeout()), mainwindowProxy, SLOT(startNoticeCrawler()));
    connect(mainwindowProxy, &FM_MainWindowProxy::inform_notice, notice, &FM_Notice::onInform_notice);

    connect(notice->trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(actSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    connect(notice->mShowMainAction,SIGNAL(triggered()),this,SLOT(show()));
    connect(notice->mExitAppAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(this, SIGNAL(minimize_notice()), notice, SLOT(onMinimize_notice()));

    //后台线程与QThread的Start与finish关联
    connect(backstageThread, &QThread::started, mainwindowProxy, &FM_MainWindowProxy::threadStarted);
    connect(backstageThread, &QThread::finished, mainwindowProxy, &FM_MainWindowProxy::threadFinished);
    //UI线程的更新信号与后台进程的getNews关联
    connect(mainwindow, &FM_MainWindow::getNews, mainwindowProxy, &FM_MainWindowProxy::getNews);
    connect(mainwindow, &FM_MainWindow::getFavorNews, mainwindowProxy, &FM_MainWindowProxy::getFavorNews);
    connect(mainwindow, &FM_MainWindow::writeFavor, mainwindowProxy, &FM_MainWindowProxy::writeFavor);

    connect(mainwindowProxy, &FM_MainWindowProxy::addNewsItemToUI, mainwindow, &FM_MainWindow::addNewsItem, Qt::QueuedConnection);
    connect(mainwindowProxy, &FM_MainWindowProxy::clearNewsinUI, mainwindow, &FM_MainWindow::clearNews);

    //显示等待gif
    connect(mainwindowProxy, &FM_MainWindowProxy::wait, waitwidget, &FM_WaitWidget::showup);
    connect(mainwindowProxy, &FM_MainWindowProxy::stopwait, waitwidget, &FM_WaitWidget::fuckoff);
    //控制MainWindow的绘制
    connect(mainwindowProxy, &FM_MainWindowProxy::wait, mainwindow, &FM_MainWindow::stopPaint);
    connect(mainwindowProxy, &FM_MainWindowProxy::stopwait, mainwindow, &FM_MainWindow::startPaint);

    connect(settingform, &FM_SettingForm::changeBackground, this, &FlyMessage::setBackgroundImage);
    connect(settingform, &FM_SettingForm::refreshAutoStart, settings, &FM_Setting::onRefreshAutoStart);
    connect(settingform, &FM_SettingForm::changeNoticeTimer, notice, &FM_Notice::set_notice_timer);
    connect(sidebar, SIGNAL(signal_refresh(QString)), mainwindow, SLOT(onRefreshNews(QString)));
    connect(sidebar, &FM_SideBar::signal_refresh, floatwindow, &FM_FloatWindow::showRefreshBtn);
    connect(sidebar, &FM_SideBar::signal_back, settingform, &FM_SettingForm::updateGlobalSettings);
    connect(sidebar, &FM_SideBar::signal_back, this, &FlyMessage::moveToMainWindow);
    connect(sidebar, &FM_SideBar::signal_back, this, &FlyMessage::returnToTopAtOnce);
    connect(sidebar, &FM_SideBar::signal_favor, mainwindow, &FM_MainWindow::getFavorNews);
    connect(sidebar, &FM_SideBar::signal_favor, floatwindow, &FM_FloatWindow::hideRefreshBtn);
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
    
    if(!find_checked && main_sidebar_items[1].checked==false)
        sidebar->setBtnClicked(0);
}
