/*

  Classe para adição de créditos através do smartphone app (para futura implementação)

*/


#include "creditdialog.h"
#include "ui_creditdialog.h"

CreditDialog::CreditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditDialog)
{
    ui->setupUi(this);
}

CreditDialog::~CreditDialog()
{
    delete ui;
}


void CreditDialog::on_pushButton_clicked()//cancelar
{
    hide();
}

void CreditDialog::on_pushButton_2_clicked()//recarregar
{

    comingDialog = new ComingDialog(this);
    comingDialog->showMaximized();
}
