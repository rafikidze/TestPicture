#include "viewdatamodel.h"
#include "qdebug.h"

////////////////////////////////////////////////////////
/// \brief ViewDataModel::ViewDataModel
/// Конструктор
ViewDataModel::ViewDataModel()
{
}
////////////////////////////////////////////
/// \brief ViewDataModel::data
/// \param index
/// \param role
/// \return
/// Переопределенная функция
QVariant ViewDataModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() ) { return QVariant(); }
        QString a = ar[index.row()];
    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0: return a;
        default: break;
        }
      break;
    }
    return QVariant();

}

///////////////////////////////////////////////////////////////////////////////////
/// \brief ViewDataModel::index
/// \param row
/// \param column
/// \param parent
/// \return
/// Переопределенная функция
QModelIndex ViewDataModel::index(int row, int column, const QModelIndex& parent) const
{
    if(column < columnCount( parent ) && row < rowCount( parent ))
        return createIndex( row, column );
    return QModelIndex();
}

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief ViewDataModel::headerData
/// \param section
/// \param orientation
/// \param role
/// \return
/// Переопределенная функция
QVariant ViewDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

   /* if( orientation == Qt::Vertical ) {
        return QString::number(section + 1);
    }*/
    return QVariant();
}

///////////////////////////////////////////////////////////
/// \brief ViewDataModel::rowCount
/// \param parent
/// \return
/// Переопределенная функция
int ViewDataModel::rowCount(const QModelIndex &parent) const
{
    return ar.size();
}


////////////////////////////////////////////////////////////
/// \brief ViewDataModel::columnCount
/// \param parent
/// \return
/// Переопределенная функция
int ViewDataModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

////////////////////////////////////////
/// \brief ViewDataModel::add_row
/// \param tXML данные строки
/// Функция добавляет строку в массив векторов
void ViewDataModel::add_row(QString str)
{
    beginResetModel();
    ar.append(str);
    endResetModel();
}

/////////////////////////////////////
/// \brief ViewDataModel::clear_table
/// Функция очищает массив данных
void ViewDataModel::clear_table()
{
    beginResetModel();
    ar.clear();
    endResetModel();
}

//////////////////////////////////////
/// \brief ViewDataModel::remove_row
/// \param row номер строки
/// Функция удаляет определенную строку
void ViewDataModel::remove_row(int row)
{
    beginResetModel();
    ar.remove(row);
    endResetModel();
}



void ViewDataModel::change_data(QVector<QString> new_ar)
{
    beginResetModel();
    ar = new_ar;
    endResetModel();
}
