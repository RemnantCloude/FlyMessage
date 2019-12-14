#ifndef NEWS_H
#define NEWS_H

#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QGridLayout>
#include <QPalette>
#include <QPushButton>

class News : public QWidget
{
    Q_OBJECT
public:
    explicit News(QWidget *parent, QString title, QString time, QString tpye, QString abstract, bool needfavor);
    ~News();

    QLabel *title_Lab;
    QLabel *time_Lab;
    QLabel *type_Lab;
    QLabel *abstract_Lab;
    QPushButton *favor_Btn;
    QGridLayout *thislayout;
    QFrame *line;

    bool isFavor;

signals:
    void FavorNews(bool);

public slots:
    void changeFavor(bool);

protected:
    void initComponents();
    void initSignalAndSlot();
    void setThisLayout();
    void setThisStyle(QString title, QString time, QString tpye, QString abstract);
    void mousePressEvent ( QMouseEvent * event );
};

#endif // NEWS_H
