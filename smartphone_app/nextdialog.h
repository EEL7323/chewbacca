#ifndef NEXTDIALOG_H
#define NEXTDIALOG_H

#include <QDialog>
#include "mytcpdialog.h"
#include "enterdialog.h"
#include "creditdialog.h"
#include "transactionsdialog.h"
#include "mytcpsocket.h"
#include "file.h"

namespace Ui {
class NextDialog;
}

class NextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NextDialog(QWidget *parent = 0);
    ~NextDialog();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

private:

    Ui::NextDialog *ui;
    MyTcpDialog *mytcpDialog;
    EnterDialog *enterDialog;
    CreditDialog *creditDialog;
    TransactionsDialog *transactionsDialog;
};

#endif // NEXTDIALOG_H
