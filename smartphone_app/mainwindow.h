#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nextdialog.h"
#include "warningdialog.h"

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
    void on_actionbuttom_triggered();

    void on_actionText_changed();

    void on_Mat_ok_clicked();

    void on_usuario_text_cursorPositionChanged(int arg1, int arg2);

    void on_passe_text_cursorPositionChanged(int arg1, int arg2);

    void on_usuario_text_editingFinished();


private:
    Ui::MainWindow *ui;
    NextDialog *nextDialog;
    WarningDialog *warningDialog;
};

#endif // MAINWINDOW_H
