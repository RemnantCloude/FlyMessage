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
    
    void getNews(QString web);
    
    QVBoxLayout *thislayout;
    QScrollArea *s;
    QString website;

    bool is_Settings; //设置界面
    
signals:

public slots:
    void switchMode(QString web);
    
protected:
    void init();
    void initSignalAndSlot();
    
    void setThisLayout();
    void setThisStyle();
    
    QJsonObject readJson(QString filename);
    void paintEvent(QPaintEvent *event);
};

#endif // MAIN_WINDOW_H
