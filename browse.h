#ifndef BROWSE_H
#define BROWSE_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDir>

namespace Ui {
class Browse;
}
//////////////////////////////////
/// \brief Browse::Browse
/// \param parent
/// Класс представления дерева каталогов
class Browse : public QDialog
{
    Q_OBJECT

public:
    explicit Browse(QWidget *parent = nullptr);
    ~Browse();

private slots:
    void on_pButCancel_clicked();
    void on_pButOK_clicked();

private:
    Ui::Browse *ui;
    QFileSystemModel *model;
signals:
    void sig_way(QString str);
};

#endif // BROWSE_H
