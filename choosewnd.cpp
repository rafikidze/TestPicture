#include "choosewnd.h"
#include "ui_choosewnd.h"

ChooseWnd::ChooseWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseWnd)
{
    ui->setupUi(this);
    browse = new Browse(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    connect(browse, SIGNAL(sig_way(QString)), this, SLOT(set_way_str(QString)));

}

ChooseWnd::~ChooseWnd()
{
    delete ui;
}

void ChooseWnd::on_pButOpen_clicked()
{
    browse->show();
}
void ChooseWnd::set_way_str(QString str)
{
    // установить в таблицу имя полученной картинки
    //QString
    ui->tableWidget->insertRow(ui->tableWidget->rowCount() );
    ui->tableWidget->setItem (ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(str));
    // передать путь дальше в отображение картинок
}
