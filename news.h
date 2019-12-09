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
    explicit News(QWidget *parent, QString title, QString time, QString tpye, QString abstract);
    ~News();

    QLabel *title_Lab;
    QLabel *time_Lab;
    QLabel *type_Lab;
    QLabel *abstract_Lab;
    QVBoxLayout *thislayout;
    QPalette pal;
    QFrame *line;

protected:
    void initComponents();
    void initSignalAndSlot();
    void mousePressEvent ( QMouseEvent * event );
    void setThisLayout();
    void setThisStyle(QString title, QString time, QString tpye, QString abstract);
    void paintEvent(QPaintEvent *event);
};

#endif // NEWS_H
