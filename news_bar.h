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

    QPushButton* source1_Btn;
    QPushButton* source2_Btn;
    QPushButton* source3_Btn;
    QPushButton* source4_Btn;
    QPushButton* source5_Btn;

signals:

public slots:

private:

protected:
    void initComponents();
    void initSignalAndSlot();
    
    void setThisLayout();
    void setThisStyle();
};

#endif // NEWS_BAR_H