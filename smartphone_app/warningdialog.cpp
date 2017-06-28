#include "warningdialog.h"
#include "ui_warningdialog.h"
#include "mytcpsocket.h"
#include "file.h"

WarningDialog::WarningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarningDialog)
{
    ui->setupUi(this);

}

WarningDialog::~WarningDialog()
{
    delete ui;
}



void WarningDialog::on_pushButton_clicked()
{

    File r;
    QString mFilename = "log.txt";
    QString Log = r.Read(mFilename, Log);
    qDebug() << Log;
    //ui->warningText->setText(Log);

    if(Log == "OK"){
        Log = "Informações Atualizadas";

    }

    else {
        Log = "Não foi possivel conectar ao servidor utilizando a matricula digitada";
    }
   ui->warningText->setText(Log);
}

void WarningDialog::on_pushButton_2_clicked()
{
    hide();
}
