#ifndef TITLE_BAR_H
#define TITLE_BAR_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QString>
#include <QPushButton>
#include <QLabel>

class MainWindow;

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

    
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    //TODO:删除后控件会错位
    void resizeEvent(QResizeEvent* event);

    MainWindow* thisparent;//父窗口
    
    QPushButton* min_Btn; // 显示最大或者最小的图标
    QPushButton* max_Btn; // 最大化按钮
    QPushButton* close_Btn;// 关闭按钮
    QPushButton* setting_Btn;// 设置按钮
    QPushButton* skin_Btn;// 皮肤设置按钮
    QPushButton* mode_Btn;// 模式切换按钮
    QLabel* icon_Lab; // 图标
    QLabel* title_Lab; // 标题

signals:
    void mouseDoubleClick(bool);

private slots:
    void onSetting(bool);//TODO:
    void onSkin(bool);//TODO:

private:

protected:
    void initComponents();
    void initSignalAndSlot();
    
    void setThisLayout();
    void setThisStyle();
};

#endif // TITLE_BAR_H
