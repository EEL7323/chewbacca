/*
 Ui principal do smartphone app
 Exibe informações de user_id, total de pessoas no RU e saldo

*/


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

void NextDialog::on_pushButton_4_clicked()// entrar no ru
{
    enterDialog = new EnterDialog(this);
    enterDialog->showMaximized();
}

void NextDialog::on_pushButton_6_clicked()//connected
{
    QString Matricula, Senha, Pessoas, Saldo, Log;
    QString mFilename = "matricula.txt";
    MyTcpSocket w;
    w.ConnectInicial();
    qDebug() << "aqui";
    w.ConnectContador();
    File s;
    Matricula = s.Read(mFilename, Matricula);
    qDebug() << Matricula;
    mFilename = "senha.txt";
    Senha = s.Read(mFilename, Senha);
    mFilename = "pessoas.txt";
    Pessoas = s.Read(mFilename, Pessoas);
    mFilename = "saldo.txt";
    Saldo = s.Read(mFilename, Saldo);
    ui->matricula->setText(Matricula);
    ui->pessoas->setText(Pessoas);
    ui->saldo->setText(Saldo);
    //hide();
    mytcpDialog = new MyTcpDialog(this);
    mytcpDialog->showMaximized();

}

void NextDialog::on_pushButton_7_clicked()//transactions
{
    transactionsDialog = new TransactionsDialog(this);
    transactionsDialog -> show();
}

void NextDialog::on_pushButton_5_clicked() //credit
{
    creditDialog = new CreditDialog(this);
    creditDialog ->showMaximized();
}
