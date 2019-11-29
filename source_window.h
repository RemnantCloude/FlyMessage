#ifndef SOURCE_WINDOW_H
#define SOURCE_WINDOW_H

#include <QWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>

class source : public QWidget
{
    Q_OBJECT
public:
    explicit source(QWidget *parent = nullptr);
    ~source();

    QCheckBox *source1_Chk;
    QCheckBox *source2_Chk;
    QCheckBox *source3_Chk;
    QCheckBox *source4_Chk;
    QCheckBox *source5_Chk;

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

#endif // SOURCE_WINDOW_H
