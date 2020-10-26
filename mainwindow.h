#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "choosewnd.h"
#include "workwnd.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pButOpenChooseWnd_clicked();

    void on_pButOpenWorkWnd_clicked();

private:
    Ui::MainWindow *ui;
    ChooseWnd *chooseWnd;
    WorkWnd *workwnd;
};

#endif // MAINWINDOW_H
