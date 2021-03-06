#ifndef CREDITDIALOG_H
#define CREDITDIALOG_H

#include <QDialog>
#include "comingdialog.h"

namespace Ui {
class CreditDialog;
}

class CreditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreditDialog(QWidget *parent = 0);
    ~CreditDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CreditDialog *ui;
    ComingDialog *comingDialog;

};

#endif // CREDITDIALOG_H
