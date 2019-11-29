#ifndef BOOKMARKS_WINDOW_H
#define BOOKMARKS_WINDOW_H

#include <QWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>

class bookmarks : public QWidget
{
    Q_OBJECT
public:
    explicit bookmarks(QWidget *parent = nullptr);
    ~bookmarks();

    QTextEdit *webpage1_Tex;
    QTextEdit *webpage2_Tex;

    QPushButton *delete1_Btn;
    QPushButton *delete2_Btn;

signals:

public slots:
    

private:
protected:
    void initComponents();
    void initSignalAndSlot();

    void setThisLayout();
    void setThisStyle();
};

#endif // BOOKMARKS_WINDOW_H
