#ifndef MYTCPDIALOG_H
#define MYTCPDIALOG_H

#include <QDialog>

namespace Ui {
class MyTcpDialog;
}

class MyTcpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyTcpDialog(QWidget *parent = 0);
    ~MyTcpDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MyTcpDialog *ui;
};

#endif // MYTCPDIALOG_H
