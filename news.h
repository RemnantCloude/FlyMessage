#ifndef NEWS_H
#define NEWS_H

#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QPalette>

class News : public QWidget
{
    Q_OBJECT
public:
    explicit News(QWidget *parent, QString title, QString time, QString abstract);
    ~News();

    QLabel *title_Lab;
    QLabel *time_Lab;
    QLabel *abstract_Lab;
    QVBoxLayout *thislayout;
    QPalette pal;

signals:

public slots:

protected:
    void initComponents();
    void initSignalAndSlot();

    void setThisLayout();
    void setThisStyle(QString title, QString time, QString abstract);
};

#endif // NEWS_H
