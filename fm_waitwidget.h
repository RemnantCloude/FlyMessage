#ifndef WAITWIDGET_H
#define WAITWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class FM_WaitWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FM_WaitWidget(QWidget *parent = nullptr);
    QLabel *image;
    QHBoxLayout *hLayout;
    QMovie *gif;
public slots:
    void showup();
    void fuckoff();
private:

};

#endif // WAITWIDGET_H
