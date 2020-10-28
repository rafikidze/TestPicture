#include "choosewnd.h"
#include "ui_choosewnd.h"
////////////////////////////////
/// \brief ChooseWnd::ChooseWnd
/// \param parent
/// Конструктор
ChooseWnd::ChooseWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseWnd)
{
    ui->setupUi(this);
    model = new ViewDataModel();
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
//////////////////////////////
/// \brief ChooseWnd::~ChooseWnd
/// Деструктор
ChooseWnd::~ChooseWnd()
{
    delete model;
    delete ui;
}
/////////////////////////////////////////
/// \brief ChooseWnd::on_pButOpen_clicked
/// Функция открытия файла
void ChooseWnd::on_pButOpen_clicked()
{
    QFileDialog dialog(this, tr("Открыть файл"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}

}
////////////////////////////////////////////////
/// \brief ChooseWnd::initializeImageFileDialog
/// \param dialog
/// \param acceptMode
/// Функция выбора изображения
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

////////////////////////////////////////////////
/// \brief ChooseWnd::loadFile
/// \param fileName имя файла
/// \return
/// Функция отправляет имя файла в таблицу и передает сигнал в Рабочее окно
bool ChooseWnd::loadFile(const QString &fileName)
{
    QString name_file(get_file_name(fileName));
    if(!name_file.isEmpty())
    {
        set_name_to_table(name_file);
        emit sig_send_pix(fileName);
        return true;
    }
    else
    {
        QMessageBox::warning(this,trUtf8("Уведомление"),
                               trUtf8("Не удалось открыть файл\n"));
        return false;
    }
}

//////////////////////////////////////////////////
/// \brief ChooseWnd::set_name_to_table
/// \param str
/// Функция устанавливает новое имя файла в таблицу
void ChooseWnd::set_name_to_table(QString str)
{
    // установить в таблицу имя полученной картинки
    list_pix.append(str);
    model->add_row(str);
}

////////////////////////////////////
/// \brief ChooseWnd::get_file_name
/// \param fileName
/// \return
/// Парсинг имени файла из пути
QString ChooseWnd::get_file_name(const QString &fileName)
{
    QString name;
    QStringList fileObject;
    fileObject = fileName.split('/');
    name = fileObject[ fileObject .size() - 1 ];
    return name;
}

///////////////////////////////////////
/// \brief ChooseWnd::on_pButUp_clicked
/// Перемещение картинки назад
void ChooseWnd::on_pButUp_clicked()
{
    int indxrow = ui->tableView->currentIndex().row();
    if (indxrow > 0)
    {
        QString temp = list_pix.at(indxrow);
        list_pix[indxrow] = list_pix[indxrow-1];
        list_pix[indxrow-1] = temp;

        set_data_to_table(list_pix);
        emit sig_change_up(indxrow);
    }
}

//////////////////////////////////////////////////////
/// \brief ChooseWnd::set_data_to_table
/// \param ar
/// Изменить данные в таблице
void ChooseWnd::set_data_to_table(QVector<QString> ar)
{
    model->change_data(ar);
}

/////////////////////////////////////////
/// \brief ChooseWnd::on_pButDown_clicked
/// Переместить картинку вперед
void ChooseWnd::on_pButDown_clicked()
{
    int indxrow = ui->tableView->currentIndex().row();
    if ((indxrow >= 0) && (indxrow!=list_pix.size()-1))
    {
        QString temp = list_pix.at(indxrow);
        list_pix[indxrow] = list_pix[indxrow+1];
        list_pix[indxrow+1] = temp;

        set_data_to_table(list_pix);
        emit sig_change_down(indxrow);
    }
}

///////////////////////////////////////////
/// \brief ChooseWnd::on_pButDelete_clicked
/// Удалить картинку
void ChooseWnd::on_pButDelete_clicked()
{
    int indxrow = ui->tableView->currentIndex().row();

    if(!list_pix.isEmpty() && (list_pix.size() > indxrow) && (indxrow>=0))
    {
        list_pix.remove(indxrow);
        set_data_to_table(list_pix);
        emit sig_del_pix(indxrow);
    }
}

//////////////////////////////////////////
/// \brief ChooseWnd::on_pButMult2_clicked
/// Функция увеличения размера картинки в 2 раза
void ChooseWnd::on_pButMult2_clicked()
{
    emit sig_scale_mult_2();
}

/////////////////////////////////////////
/// \brief ChooseWnd::on_pButDiv2_clicked
/// Функция уменьшения размера картинки в 2 раза
void ChooseWnd::on_pButDiv2_clicked()
{
    emit sig_scale_div_2();
}

////////////////////////////////////////
/// \brief ChooseWnd::slot_set_focus
/// \param value индекс текущей картинки
/// Установить текущую картинку
void ChooseWnd::slot_set_focus(int value)
{
    list_pix.move(value, list_pix.size()-1);
    set_data_to_table(list_pix);
}
