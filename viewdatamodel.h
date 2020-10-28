#ifndef XMLTABLE_H
#define XMLTABLE_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QObject>

/////////////////////////////////////////////////
/// \brief The ViewDataModel class
/// Класс кастомной табличной модели данных
class ViewDataModel : public QAbstractTableModel
{
public:
    ViewDataModel();
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    void change_data(QVector<QString>);
    void add_row(QString);
    QVector<QString> ar;

};


#endif // XMLTABLE_H

