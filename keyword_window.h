#ifndef KEYWORD_WINDOW_H
#define KEYWORD_WINDOW_H

#include <QWidget>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>

class keyword : public QWidget
{
    Q_OBJECT
public:
    explicit keyword(QWidget *parent = nullptr);
    ~keyword();

    QCheckBox *keyword1_Chk;
    QCheckBox *keyword2_Chk;
    QCheckBox *keyword3_Chk;
    QCheckBox *keyword4_Chk;
    QCheckBox *keyword5_Chk;

    QPushButton *confirm_Btn;
    QPushButton *cancel_Btn;

signals:

public slots:

private:
protected:
    void initComponents();
    void initSignalAndSlot();

    void setThisLayout();
    void setThisStyle();
};

#endif // KEYWORD_WINDOW_H
