#include "webwizardform.h"
#include "ui_webwizardform.h"

WebWizardForm::WebWizardForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebWizardForm)
{
    ui->setupUi(this);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &WebWizardForm::close);
    currentPage = ui->stackedWidget->currentIndex();
    setPageNum(currentPage);
}

WebWizardForm::~WebWizardForm()
{
    delete ui;
}

void WebWizardForm::setPageNum(int page)
{
    currentPage = page;
    ui->stackedWidget->setCurrentIndex(currentPage);
    switch (page) {
    case 0:
        ui->stepBtn2->setEnabled(false);
        ui->stepBtn3->setEnabled(false);
        ui->stepBtn4->setEnabled(false);
        ui->backBtn->setEnabled(false);
        ui->nextBtn->setText("下一步");
        break;
    case 1:
        ui->stepBtn2->setEnabled(true);
        ui->stepBtn3->setEnabled(false);
        ui->stepBtn4->setEnabled(false);
        ui->backBtn->setEnabled(true);
        ui->nextBtn->setText("下一步");
        break;
    case 2:
        ui->stepBtn2->setEnabled(true);
        ui->stepBtn3->setEnabled(true);
        ui->stepBtn4->setEnabled(false);
        ui->backBtn->setEnabled(true);
        ui->nextBtn->setText("下一步");
        break;
    case 3:
        ui->stepBtn2->setEnabled(true);
        ui->stepBtn3->setEnabled(true);
        ui->stepBtn4->setEnabled(true);
        ui->backBtn->setEnabled(true);
        ui->nextBtn->setText("完成");
        break;
    default:
        break;
    }
}

void WebWizardForm::on_nextBtn_clicked()
{
    setPageNum(++currentPage);
}

void WebWizardForm::on_backBtn_clicked()
{
    setPageNum(--currentPage);
}

void WebWizardForm::on_stepBtn1_clicked()
{
    setPageNum(0);
}

void WebWizardForm::on_stepBtn2_clicked()
{
    setPageNum(1);
}

void WebWizardForm::on_stepBtn3_clicked()
{
    setPageNum(2);
}

void WebWizardForm::on_stepBtn4_clicked()
{
    setPageNum(3);
}
