#ifndef FM_CONNECTFORM_H
#define FM_CONNECTFORM_H

#include <QWidget>

namespace Ui {
class ConnectForm;
}

class FM_ConnectForm : public QWidget
{
public:
    explicit FM_ConnectForm(QWidget *parent = nullptr);
    ~FM_ConnectForm();
private:
    Ui::ConnectForm *ui;
};

#endif // FM_CONNECTFORM_H
