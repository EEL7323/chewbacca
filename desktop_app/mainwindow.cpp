#include "mainwindow.h"
#include "requestapi.h"
#include "ui_mainwindow.h"

class MainWindow::Data
{
public:
    Data() : m_r(NULL) {}

    RequestApi* r(QObject *parent) {
        if (!m_r) m_r = new RequestApi(parent);
        return m_r;
    }

    RequestApi *m_r;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    d(new Data)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete d;
}

void MainWindow::on_pushButton_cadastro_clicked()
{
    int statusCode;
    QString s = "http://127.0.0.1:5000/user";

    QJsonObject json;
    json.insert("username", ui->lineEdit_cadastro_username->text());
    json.insert("password",ui->lineEdit_cadastro_password->text());
    json.insert("cardID", ui->lineEdit_cadastro_cardID->text());

    d->r(this)->makeRequestPOST(s,json);
    ui->lineEdit_cadastro_cardID->clear();
    ui->lineEdit_cadastro_password->clear();
    ui->lineEdit_cadastro_username->clear();

}

void MainWindow::on_pushButton_credito_clicked()
{
    ui->plainTextEdit->appendPlainText("Credito");
}

void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
}
