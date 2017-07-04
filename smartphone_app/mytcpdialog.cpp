/*

Informa ao usuario se a conexão com o servidor foi estabelecida corretamente.

*/

#include "mytcpdialog.h"
#include "ui_mytcpdialog.h"
#include "file.h"

MyTcpDialog::MyTcpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyTcpDialog)
{
    ui->setupUi(this);
}

MyTcpDialog::~MyTcpDialog()
{
    delete ui;
}

void MyTcpDialog::on_pushButton_clicked()//log
{
    File r;
    QString mFilename = "log.txt";
    QString Log = "";
    Log = r.Read(mFilename, Log);
    qDebug() << Log;


    if(Log == "OK"){
        Log = "Informações Atualizadas";

    }

    else {
        Log = "Não foi possivel conectar ao servidor utilizando a matricula digitada";
    }
   ui->warningText->setText(Log);
}

void MyTcpDialog::on_pushButton_2_clicked()//sair
{
    hide();
}
