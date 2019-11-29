#ifndef SIDE_BAR_H
#define SIDE_BAR_H

#include <QWidget>
#include <QtWidgets/QPushButton>

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar();

    QPushButton *settings_Btn;
    QPushButton *bookmarks_Btn;

signals:

public slots:

protected:
    void initComponents();
    void initSignalAndSlot();
    
    void setThisLayout();
    void setThisStyle();
};

#endif // SIDE_BAR_H
