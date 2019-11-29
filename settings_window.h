#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QPushButton>

class settings : public QWidget
{
    Q_OBJECT
public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

    QPushButton *keywordSettings_Btn; // 关键词设置
    QPushButton *sourceSettings_Btn; // 来源网站
    QPushButton *refreshSettings_Btn; // 刷新设置
    QPushButton *informSettings_Btn; // 消息设置

signals:

public slots:
    void openKeyword(bool);
    void openSource(bool);
    void openRefresh(bool);
    void openInform(bool);

protected:
    void initComponents();
    void initSignalAndSlot();

    void setThisLayout();
    void setThisStyle();
};

#endif // SETTINGS_H
