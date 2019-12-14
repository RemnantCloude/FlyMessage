#ifndef WEBWIZARDFORM_H
#define WEBWIZARDFORM_H

#include <QWidget>

namespace Ui {
class WebWizardForm;
}

class WebWizardForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit WebWizardForm(QWidget *parent = nullptr);
    ~WebWizardForm();
    void setPageNum(int page);
    
private slots:
    void on_nextBtn_clicked();
    
    void on_backBtn_clicked();
    
    void on_stepBtn1_clicked();
    
    void on_stepBtn2_clicked();
    
    void on_stepBtn3_clicked();
    
private:
    Ui::WebWizardForm *ui;
    int currentPage = 1;
};

#endif // WEBWIZARDFROM_H
