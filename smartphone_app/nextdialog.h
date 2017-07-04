#ifndef NEXTDIALOG_H
#define NEXTDIALOG_H

#include <QDialog>
#include "warningdialog.h"
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
    void on_label_linkActivated(const QString &link);

    void on_Ent_mat_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_clicked(bool checked);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::NextDialog *ui;
    WarningDialog *warningDialog;
    CreditDialog *creditDialog;
    TransactionsDialog *transactionsDialog;
};

#endif // NEXTDIALOG_H
