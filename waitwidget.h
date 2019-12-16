#ifndef WAITWIDGET_H
#define WAITWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class WaitWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaitWidget(QWidget *parent = nullptr);

public slots:
    void showup();
    void fuckoff();
private:
    QLabel *image;
    QHBoxLayout *hLayout;
    QMovie *gif;
};

#endif // WAITWIDGET_H
