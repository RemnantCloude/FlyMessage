#ifndef REFRESH_WINDOW_H
#define REFRESH_WINDOW_H

#include <QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

class refresh : public QWidget
{
    Q_OBJECT
public:
    explicit refresh(QWidget *parent = nullptr);
    ~refresh();

    QLineEdit *refreshTime_Tex;
    QLabel *time_Lab;

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

#endif // REFRESH_WINDOW_H
