#ifndef FLOAT_WINDOW_H
#define FLOAT_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class FlyMessage;

class FM_FloatWindow : public QWidget
{
public:
    explicit FM_FloatWindow(QWidget *parent = nullptr);
    ~FM_FloatWindow();
    
    QPushButton *refresh_Btn;
    QPushButton *returnToTop_Btn;

    QGridLayout *thislayout;

signals:

public slots:
    void hideRefreshBtn();
    void showRefreshBtn();

protected:
    void initComponents();
    void setComponentsLayout();
    void setComponentsStyle();
    void paintEvent(QPaintEvent *event);
};

#endif // FLOAT_WINDOW_H
