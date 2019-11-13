#ifndef NEWS_ARTICLE_H
#define NEWS_ARTICLE_H

#include <QWidget>
#include <QtWidgets/QTextEdit>

class NewsArticle : public QWidget
{
    Q_OBJECT
public:
    explicit NewsArticle(QWidget *parent = nullptr);
    ~NewsArticle();

    QTextEdit *news1_Tex;
    QTextEdit *news2_Tex;
    QTextEdit *news3_Tex;
    QTextEdit *news4_Tex;
    QTextEdit *news5_Tex;

    void json(void);

signals:

public slots:

private:
    void initComponents();
    void initSignalAndSlot();
    
    void setThisLayout();
    void setThisStyle();
};

#endif // NEWS_ARTICLE_H