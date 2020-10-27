#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chooseWnd = new ChooseWnd(this);
    workwnd = new WorkWnd(this);

    connect(chooseWnd, SIGNAL(sig_send_pix(QString)), workwnd, SLOT(slot_get_pix(QString)));
    connect(chooseWnd, SIGNAL(sig_del_pix(int)), workwnd, SLOT(slot_del_pix(int)));
    connect(chooseWnd, SIGNAL(sig_change_up(int)), workwnd, SLOT(slot_change_up(int)));
    connect(chooseWnd, SIGNAL(sig_change_down(int)), workwnd, SLOT(slot_change_down(int)));
    connect(chooseWnd, SIGNAL(sig_scale_mult_2()), workwnd, SLOT(on_pButMult2_clicked()));
    connect(chooseWnd, SIGNAL(sig_scale_div_2()), workwnd, SLOT(on_pButDiv2_clicked()));


}

MainWindow::~MainWindow()
{
    disconnect(chooseWnd, SIGNAL(sig_send_pix(QString)), workwnd, SLOT(slot_get_pix(QString)));
    disconnect(chooseWnd, SIGNAL(sig_del_pix(int)), workwnd, SLOT(slot_del_pix(int)));
    disconnect(chooseWnd, SIGNAL(sig_change_up(int)), workwnd, SLOT(slot_change_up(int)));
    disconnect(chooseWnd, SIGNAL(sig_change_down(int)), workwnd, SLOT(slot_change_down(int)));
    disconnect(chooseWnd, SIGNAL(sig_scale_mult_2()), workwnd, SLOT(on_pButMult2_clicked()));
    disconnect(chooseWnd, SIGNAL(sig_scale_div_2()), workwnd, SLOT(on_pButDiv2_clicked()));
    delete workwnd;
    delete chooseWnd;
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
