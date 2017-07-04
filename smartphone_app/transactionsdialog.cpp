/*

Função com a finalidade de exibir as transaçoes realizadas pelo usuario.

*/
#include "transactionsdialog.h"
#include "ui_transactionsdialog.h"
#include "file.h"
#include <QTextStream>

TransactionsDialog::TransactionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionsDialog)
{
    ui->setupUi(this);
}

TransactionsDialog::~TransactionsDialog()
{
    delete ui;
}

void TransactionsDialog::on_pushButton_clicked()//transaçoes
{
    File w;

    QString Transacoes;
    QString mFilename = "transactions.txt";
    Transacoes = w.Read(mFilename, Transacoes);
    ui->TransactionsDialog_2->appendPlainText(Transacoes);
}

void TransactionsDialog::on_pushButton_2_clicked()//sair
{
    hide();
}

