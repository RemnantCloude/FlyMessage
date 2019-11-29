#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTextEdit *news1_Tex;
    QTextEdit *news2_Tex;
    QTextEdit *news3_Tex;
    QTextEdit *news4_Tex;
    QTextEdit *news5_Tex;

    QPushButton *bookmarks1_Btn;
    QPushButton *bookmarks2_Btn;
    QPushButton *bookmarks3_Btn;
    QPushButton *bookmarks4_Btn;
    QPushButton *bookmarks5_Btn;

    QPushButton *refresh_Btn;
    QPushButton *returnToTop_Btn;

    void json(void);

signals:

public slots:

protected:
    void initComponents();
    void initSignalAndSlot();
    
    void setThisLayout();
    void setThisStyle();
};

#endif // MAIN_WINDOW_H
