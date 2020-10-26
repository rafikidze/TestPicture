#include "choosewnd.h"
#include "ui_choosewnd.h"

#include <qdebug.h>

ChooseWnd::ChooseWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseWnd)
{
    ui->setupUi(this);
    model = new ViewDataModel();
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

ChooseWnd::~ChooseWnd()
{
    delete ui;
}

void ChooseWnd::on_pButOpen_clicked()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}

}
void ChooseWnd::initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    for (const QByteArray &mimeTypeName : supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

bool ChooseWnd::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    QString name_file(get_file_name(fileName));

    qDebug() << fileName;

    if(!name_file.isEmpty()) set_name_to_table(name_file);
    else ; // ВЫВОДИ ОШИБКУ


    /*reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }
//! [2]

    setImage(newImage);

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);*/
    return true;
}
void ChooseWnd::set_name_to_table(QString str)
{
    // установить в таблицу имя полученной картинки
    list_pix.append(str);
    model->add_row(str);


    // передать путь дальше в отображение картинок
}
QString ChooseWnd::get_file_name(const QString &fileName)
{
    QString name;
    QStringList fileObject;
    fileObject = fileName.split('/');
    name = fileObject[ fileObject .size() - 1 ];

    qDebug() << name;
    return name;
}

void ChooseWnd::on_pButUp_clicked()
{
    int indxrow = ui->tableView->currentIndex().row();
    if (indxrow > 0)
    {
        QString temp = list_pix.at(indxrow);
        list_pix[indxrow] = list_pix[indxrow-1];
        list_pix[indxrow-1] = temp;

        set_data_to_table(list_pix);

    }
}

void ChooseWnd::set_data_to_table(QVector<QString> ar)
{
    model->change_data(ar);
}

void ChooseWnd::on_pButDown_clicked()
{
    int indxrow = ui->tableView->currentIndex().row();
    if ((indxrow >= 0) && (indxrow!=list_pix.size()-1))
    {
        QString temp = list_pix.at(indxrow);
        list_pix[indxrow] = list_pix[indxrow+1];
        list_pix[indxrow+1] = temp;

        set_data_to_table(list_pix);

    }
}

void ChooseWnd::on_pButDelete_clicked()
{
    int indxrow = ui->tableView->currentIndex().row();

    if(!list_pix.isEmpty() && (list_pix.size() > indxrow))
    {
        list_pix.remove(indxrow);
        set_data_to_table(list_pix);
    }
}
