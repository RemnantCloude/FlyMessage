#ifndef TITLE_BAR_H
#define TITLE_BAR_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QString>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class FlyMessage;

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    FlyMessage* thisparent;//父窗口

    QHBoxLayout* titleLayout;
    QSpacerItem* Spacer;
    QPushButton* min_Btn; // 显示最大或者最小的图标
    QPushButton* max_Btn; // 最大化按钮
    QPushButton* close_Btn;// 关闭按钮
    QPushButton* settings_Btn;// 设置按钮
    QLabel* icon_Lab; // 图标
    QLabel* title_Lab; // 标题

protected:
    void initComponents();
    void initSignalAndSlot();
    
    void setThisLayout();
    void setThisStyle();
};

#endif // TITLE_BAR_H
