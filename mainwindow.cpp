#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chooseWnd = new ChooseWnd(this);
    workwnd = new WorkWnd(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pButOpenChooseWnd_clicked()
{
    chooseWnd->show();
}

void MainWindow::on_pButOpenWorkWnd_clicked()
{
    workwnd->show();
}
