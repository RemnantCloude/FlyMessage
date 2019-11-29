#ifndef NEWS_BAR_H
#define NEWS_BAR_H

#include <QWidget>
#include <QtWidgets/QPushButton>

class NewsBar : public QWidget
{
    Q_OBJECT
public:
    explicit NewsBar(QWidget *parent = nullptr);
    ~NewsBar();

    QPushButton *settings_Btn;
    QPushButton *bookmarks_Btn;

signals:

public slots:
    void openSettings(bool);
    void openBookmarks(bool);

private:
protected:
    void initComponents();
    void initSignalAndSlot();
    
    void setThisLayout();
    void setThisStyle();
};

#endif // NEWS_BAR_H
