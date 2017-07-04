#ifndef TRANSACTIONSDIALOG_H
#define TRANSACTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class TransactionsDialog;
}

class TransactionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionsDialog(QWidget *parent = 0);
    ~TransactionsDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TransactionsDialog *ui;
};

#endif // TRANSACTIONSDIALOG_H
