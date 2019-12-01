#include "title_bar.h"
#include "FlyMessage.h"

#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QStyle>
#include <QVBoxLayout>
#include <QFontDatabase>

#define BTN_WIDTH   (40)
#define BTN_HEIGHT  (30)

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    thisparent = (FlyMessage*)parentWidget();// 获得父窗口的指针

    initComponents();// 初始化组件
    initSignalAndSlot();// 初始化信号与槽

    setThisLayout();// 布局设置
    setThisStyle();// 样式设置
}

TitleBar::~TitleBar()
{

}

void TitleBar::initComponents()
{
    icon_Lab     = new QLabel(this);
    title_Lab    = new QLabel(this);
    skin_Btn     = new QPushButton(this);
    min_Btn      = new QPushButton(this);
    max_Btn      = new QPushButton(this);
    close_Btn    = new QPushButton(this);
    settings_Btn = new QPushButton(this);
}

void TitleBar::initSignalAndSlot()
{
    connect(skin_Btn, SIGNAL(clicked(bool)), SLOT(onSkin(bool)));
    connect(settings_Btn, SIGNAL(clicked(bool)), SLOT(onSettings(bool)));
}
// TODO:重新设置布局
void TitleBar::setThisLayout()
{
    setFixedHeight(50);
    // 设置控件布局
    icon_Lab->setGeometry   (0, 0, 50, 50);
    title_Lab->setGeometry  (55, 0, 4*BTN_WIDTH, BTN_HEIGHT);
    
    close_Btn->setGeometry  (width () - 1*BTN_WIDTH, 0,   BTN_WIDTH, BTN_HEIGHT);
    max_Btn->setGeometry    (width () - 2*BTN_WIDTH, 0,   BTN_WIDTH, BTN_HEIGHT);
    min_Btn->setGeometry    (width () - 3*BTN_WIDTH, 0,   BTN_WIDTH, BTN_HEIGHT);
    settings_Btn->setGeometry(width () - 4*BTN_WIDTH, 0,   BTN_WIDTH, BTN_HEIGHT);
    skin_Btn->setGeometry   (width () - 5*BTN_WIDTH, 0,   BTN_WIDTH, BTN_HEIGHT);
}

void TitleBar::setThisStyle()
{
    // 使按钮透明
    close_Btn->setFlat(true);
    min_Btn->setFlat(true);
    max_Btn->setFlat(true);
    skin_Btn->setFlat(true);
    settings_Btn->setFlat(true);

    // TODO:学习QSS
    setStyleSheet(  "QPushButton{font-size: 12pt; border-style: none; color: black;}"
                    "QPushButton:hover{background-color:gray;}"
                    "QPushButton:pressed{background-color:lightgray; color: blue;}");
    close_Btn->setStyleSheet("QPushButton{border-style: none/*;border-top-right-radius:5px*/}"
                            "QPushButton:hover{background-color:red; color: black;}"
                            "QPushButton:pressed{background-color:rgba(85, 170, 255,200); border-style: inset; }");
    title_Lab->setStyleSheet("QLabel{font-size: 12pt; color: black;}");

    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome_solid");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    // 创建字体
    QFont font;
    font.setFamily(fontFamilies.at(0));

    close_Btn->setToolTip("关闭");
    close_Btn->setFont(font);
    close_Btn->setText(QChar(0xf00d));

    min_Btn->setToolTip("最小化");
    min_Btn->setFont(font);
    min_Btn->setText(QChar(0xf2d1));

    max_Btn->setToolTip("最大化");
    max_Btn->setFont(font);
    max_Btn->setText(QChar(0xf2d0));

    settings_Btn->setToolTip("设置");
    settings_Btn->setFont(font);
    settings_Btn->setText(QChar(0xf0ad));

    skin_Btn->setToolTip("皮肤");
    skin_Btn->setFont(font);
    skin_Btn->setText(QChar(0xf553));

    QPixmap pixmap(":/images/logo");// TODO:需要换成其它大logo
    icon_Lab->setPixmap(pixmap);

    title_Lab->setText("飞讯");
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    this->thisparent->windowPos = this->thisparent->pos(); // 获得部件当前位置
    this->thisparent->mousePos = event->globalPos(); // 获得鼠标位置
    this->thisparent->dPos = thisparent->mousePos - thisparent->windowPos; // 移动后部件所在的位置
}
// 暂时先不管这个函数
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    this->thisparent->move(event->globalPos() - this->thisparent->dPos);

    // TODO:最大化移动标题栏时会变回正常大小
    // if(this->thisparent->windowState() == Qt::WindowMaximized)
    // {
    //     setWindowState( Qt::WindowNoState );
    // }

    //TODO:实现靠边时会最大化
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit mouseDoubleClick(1);
}

// TODO:可拉伸
void TitleBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    // 控件位置调整
    setThisLayout ();

    // 背景图片缩放TODO:
//     if(hasBackgroundImage){
//         QPalette pal(palette());
//         pal.setBrush(QPalette::Window,QBrush(background.scaled(event->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
//         setPalette(pal);
//     }
}

void TitleBar::onSkin(bool)
{

}

void TitleBar::onSettings(bool)
{
    emit openSettings(1);
}
