/*

  Verifica horário para que o usuário possa ou não acessar o restaurante.
  Libera o acesso do usuario ao RU.

*/
#include "enterdialog.h"
#include "ui_enterdialog.h"
#include "file.h"
#include "QTime"
#include "QDateTime"

EnterDialog::EnterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterDialog)
{
    ui->setupUi(this);
}

EnterDialog::~EnterDialog()
{
    delete ui;
}

void EnterDialog::on_pushButton_clicked()//ok
{
    QTime tempo = QTime::currentTime();
    QTime lunch1(11,30,0);
    QTime lunch2(13,30,0);
    QTime dinner1(17,30,0);
    QTime dinner2(19,30,0);


    if ((tempo > lunch1 && tempo < lunch2) || (tempo > dinner1 && tempo < dinner2))
    {
    ui->enterText->setText("Restaurante Funcionando");
    comingDialog = new ComingDialog(this);
    comingDialog->showMaximized();
    /*

    ADICIONAR PARTE REFERENTE A COMUNICAÇAO COM A PLACA

    */
    }
    else {
           ui->enterText->setText("Restaurante Fechado");
    }
}

void EnterDialog::on_pushButton_2_clicked()//sair
{
    hide();
}
