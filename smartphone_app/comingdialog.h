#ifndef COMINGDIALOG_H
#define COMINGDIALOG_H

#include <QDialog>

namespace Ui {
class ComingDialog;
}

class ComingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComingDialog(QWidget *parent = 0);
    ~ComingDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ComingDialog *ui;
};

#endif // COMINGDIALOG_H
