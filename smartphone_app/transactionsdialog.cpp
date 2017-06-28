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




void TransactionsDialog::on_pushButton_2_clicked()
{
    hide();
}

void TransactionsDialog::on_pushButton_clicked()
{
    File w;

    QString Transacoes;
    QString mFilename = "data.txt";
    Transacoes = w.Read(mFilename, Transacoes);
    Transacoes.replace(QString("event"), QString("Creditos"));
    Transacoes.replace(QString("timestamp"), QString("Data e hora"));
    ui->TransactionsDialog_2->appendPlainText(Transacoes);
}
