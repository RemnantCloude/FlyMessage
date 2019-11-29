#ifndef INFORM_WINDOW_H
#define INFORM_WINDOW_H

#include <QWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>

class inform : public QWidget
{
    Q_OBJECT
public:
    explicit inform(QWidget *parent = nullptr);
    ~inform();

    QCheckBox *source1_Chk;
    QCheckBox *source2_Chk;

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

#endif // INFORM_WINDOW_H
