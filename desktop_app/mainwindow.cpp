#include "mainwindow.h"
#include "requestapi.h"
#include "ui_mainwindow.h"
#include "mytcpsocket.h"
#include "QJsonObject"
#include "QJsonDocument"
#include "QJsonArray"


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
    json.insert("n_password",ui->lineEdit_cadastro_Npassword->text());
    json.insert("matricula", ui->lineEdit_cadastro_matricula->text());

    d->r(this)->makeRequestPOST(s,json);
    ui->lineEdit_cadastro_cardID->clear();
    ui->lineEdit_cadastro_password->clear();
    ui->lineEdit_cadastro_username->clear();
    ui->lineEdit_cadastro_Npassword->clear();
    ui->lineEdit_cadastro_matricula->clear();
}

void MainWindow::on_pushButton_credito_clicked()
{
    QString cartao = ui->lineEdit_credito_cardID->text();
    MyTcpSocket *socket = new MyTcpSocket();

    socket->setCartao(cartao);
    socket->doConnect();

    QString data = socket->getData().remove(0,153);

    int user_id = data.toInt();
    if (user_id == -1) {
        //ui->plainTextEdit->appendPlainText("Usuario nao existe");
    } else {
        QJsonObject json;
        json.insert("event_id",ui->lineEdit_credito_valor->text());
        QString s = "http://127.0.0.1:5000/transaction/"+data;
        d->r(this)->makeRequestPOST(s,json);
        //ui->plainTextEdit->appendPlainText("Usuario existe");
    }
    ui->lineEdit_credito_cardID->clear();
    ui->lineEdit_credito_valor->clear();
    //ui->plainTextEdit->appendPlainText("Credito");
}

void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
}
