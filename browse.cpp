#include "browse.h"
#include "ui_browse.h"

///////////////////////////////
/// \brief Browse::Browse
/// \param parent
/// Конструктор
Browse::Browse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Browse)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    model = new QFileSystemModel(this);
    model->setRootPath("");
    model->setNameFilters(QStringList()<< "*.png" << "*.jpg" << "*.bmp");
    model->setNameFilterDisables(false);
    ui->treeView->setModel(model);
    ui->treeView->header()->setHidden(true);
    ui->treeView->setColumnHidden(1,true);
    ui->treeView->setColumnHidden(2,true);
    ui->treeView->setColumnHidden(3,true);
}
///////////////////////////
/// \brief Browse::~Browse
/// Деструктор
Browse::~Browse()
{
    delete ui;
}

//////////////////////////////////////
/// \brief Browse::on_pButCancel_clicked
/// Нажатие на кнопку "Отмена"
void Browse::on_pButCancel_clicked()
{
    this->close();
}
///////////////////////////////////
/// \brief Browse::on_pButOK_clicked
/// Нажатие на кнопку "Ок"
void Browse::on_pButOK_clicked()
{
    QModelIndexList lst = ui->treeView->selectionModel()->selectedIndexes();
    emit sig_way(model->filePath(lst.at(0)));

    this->close();
}
