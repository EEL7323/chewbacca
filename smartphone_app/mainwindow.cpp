#include "mainwindow.h"
#include "ui_mainwindow.h"



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
    QString Matricula, j, Usuario, Passe;
    Matricula = ui->Dig_mat->text();
    j = Matricula.data()[0];
    //ui->teste_1->setText(QString::number(Matricula));


    if (j == "1" or j == "0" ) { //Considerando que as matriculas dos alunos começam com 0 ou 1
        Usuario = "Aluno";
        Passe = "R$ 1,50";
        ui->usuario_text->setText(Usuario);
        ui->passe_text->setText(Passe);


    }

    else if (j == "9") { //Considerando que as matriculas dos servidores começam com 9
        Usuario = "Servidor";
        Passe = "R$ 6,00";
        ui->usuario_text->setText(Usuario);
        ui->passe_text->setText(Passe);

    }

    else {
        ui->usuario_text->setText("Matricula Incorreta");
        ui->passe_text->setText("Matricula Incorreta");
    }

}
