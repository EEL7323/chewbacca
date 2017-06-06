#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

    void on_pushButton_cadastro_clicked();

    void on_pushButton_credito_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    class Data;
    Data *const d;
};


#endif // MAINWINDOW_H
