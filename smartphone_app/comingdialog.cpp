/*

  Ui para informar ao usuario das proximas atualizações.

*/

#include "comingdialog.h"
#include "ui_comingdialog.h"

ComingDialog::ComingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComingDialog)
{
    ui->setupUi(this);
}

ComingDialog::~ComingDialog()
{
    delete ui;
}


void ComingDialog::on_pushButton_clicked()//ok
{
    hide();
}
