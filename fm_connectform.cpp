#include "fm_connectform.h"
#include "ui_connectform.h"

FM_ConnectForm::FM_ConnectForm(QWidget *parent):
    QWidget (parent),
    ui(new Ui::ConnectForm)
{
    ui->setupUi(this);
    setWindowTitle("联系我们");
}

FM_ConnectForm::~FM_ConnectForm()
{
    delete ui;
}
