#include <QMovie>
#include "fm_waitwidget.h"

FM_WaitWidget::FM_WaitWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground);
    hLayout = new QHBoxLayout(this);
    image = new QLabel(this);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setStyleSheet("background:rgba(243,243,243,180);");
    
    gif = new QMovie(":/images/wait");
    gif->setScaledSize(QSize(329,247));
    
    image->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    image->setMaximumSize(gif->scaledSize());
    image->setMinimumSize(gif->scaledSize());
    //image->setStyleSheet("border:1px solid black");
    hLayout->addWidget(image,0,Qt::AlignHCenter);

    this->setLayout(hLayout);
    
    image->setMovie(gif);
}

void FM_WaitWidget::showup()
{
    gif->start();
    gif->setSpeed(200);
    this->show();
}

void FM_WaitWidget::fuckoff()
{
    gif->stop();
    this->hide();
}
