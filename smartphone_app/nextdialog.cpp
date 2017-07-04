#include "nextdialog.h"
#include "ui_nextdialog.h"
#include "mytcpsocket.h"
#include "mainwindow.h"
#include "file.h"
#include "transactionsdialog.h"


NextDialog::NextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NextDialog)
{

    ui->setupUi(this);
}


NextDialog::~NextDialog()
{
    delete ui;
}




void NextDialog::on_pushButton_4_clicked()
{



}

void NextDialog::on_pushButton_3_clicked()
{
    creditDialog = new CreditDialog(this);
    creditDialog ->show();
}

void NextDialog::on_pushButton_clicked()
{
    {
        QString Matricula, Senha, Pessoas, Saldo, Log;
        QString mFilename = "matricula.txt";
        File s;
        Matricula = s.Read(mFilename, Matricula);
        //qDebug() << Matricula;
        mFilename = "senha.txt";
        Senha = s.Read(mFilename, Senha);
        mFilename = "pessoas.txt";
        Pessoas = s.Read(mFilename, Pessoas);
        mFilename = "saldo.txt";
        Saldo = s.Read(mFilename, Saldo);
        ui->Ent_mat->setText(Matricula);
        ui->Ent_pes->setText(Pessoas);
        ui->Ent_sal->setText(Saldo);
        MyTcpSocket w;
        w.doConnect();
        mFilename = "log.txt";
        Log = s.Read(mFilename, Log);
        qDebug() << Log;
        warningDialog = new WarningDialog(this);
        if(Log == "ERROR") {
        hide();
        warningDialog ->show();
        }
        else {
        warningDialog ->show();
        }

    }

}

void NextDialog::on_pushButton_2_clicked()
{
    transactionsDialog = new TransactionsDialog(this);
    transactionsDialog -> show();
}
