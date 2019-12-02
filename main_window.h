#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QScrollArea>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVBoxLayout *thislayout;
    QScrollArea *s;

    bool is_Settings; //设置界面

    void getNews(void);

signals:

public slots:
    void mode(bool);

protected:
    void initComponents();
    void initSignalAndSlot();
    
    void setThisLayout();
    void setThisStyle();
    void paintEvent(QPaintEvent *event);
};

#endif // MAIN_WINDOW_H
