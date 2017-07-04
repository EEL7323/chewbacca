/*

  Ui inicial para aquisição de dados iniciais do usuario, como user_id e senha.

*/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QtCore/QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "file.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString userid, Senha, Pessoas, Saldo;
    userid = ui->matricula->text();
    Senha = ui->password->text();
    Pessoas = "0";
    Saldo = "0";

    File s;
    QString mFilename = "userid.txt";
    s.Write(mFilename, userid);
    mFilename = "senha.txt";
    s.Write(mFilename, Senha);
    mFilename = "pessoas.txt";
    s.Write(mFilename, Pessoas);
    mFilename = "saldo.txt";
    s.Write(mFilename, Saldo);
    mFilename = "log.txt";
    s.Write(mFilename, "");
    mFilename = "matricula.txt";
    s.Write(mFilename, "");
    mFilename = "nome.txt";
    s.Write(mFilename, "");
    mFilename = "transactions.txt";
    s.Write(mFilename, "");





    nextDialog = new NextDialog(this);
    nextDialog ->show();
}
