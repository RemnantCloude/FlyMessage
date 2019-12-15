#ifndef FLOAT_WINDOW_H
#define FLOAT_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class FlyMessage;

class FloatWindow : public QWidget
{
public:
    explicit FloatWindow(QWidget *parent = nullptr);
    ~FloatWindow();
    
    QPushButton *refresh_Btn;
    QPushButton *returnToTop_Btn;

    QGridLayout *thislayout;

signals:

public slots:
    void hideRefreshBtn();
    void showRefreshBtn();

protected:
    void initComponents();
    void initSignalAndSlot();
    void setThisLayout();
    void setThisStyle();
    void paintEvent(QPaintEvent *event);
};

#endif // FLOAT_WINDOW_H
