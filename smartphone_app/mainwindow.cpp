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



void MainWindow::on_Mat_ok_clicked()
{
    QString Matricula, Senha, Pessoas, Saldo;
    Matricula = ui->Dig_mat->text();
    Senha = ui->Dig_sen->text();
    Pessoas = "0";
    Saldo = "0";

    File s;
    QString mFilename = "matricula.txt";
    s.Write(mFilename, Matricula);
    mFilename = "senha.txt";
    s.Write(mFilename, Senha);
    mFilename = "pessoas.txt";
    s.Write(mFilename, Pessoas);
    mFilename = "saldo.txt";
    s.Write(mFilename, Saldo);
    mFilename = "log.txt";
    s.Write(mFilename, "");
    mFilename = "data.txt";
    s.Write(mFilename, "");





    nextDialog = new NextDialog(this);
    nextDialog ->show();

}
