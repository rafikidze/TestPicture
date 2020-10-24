#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "choosewnd.h"

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

private:
    Ui::MainWindow *ui;
    ChooseWnd *chooseWnd;
};

#endif // MAINWINDOW_H
