#ifndef CHOOSEWND_H
#define CHOOSEWND_H

#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>

#include "viewdatamodel.h"

namespace Ui {
class ChooseWnd;
}

//////////////////////////////
/// \brief The ChooseWnd class
/// Класс окна выбора
class ChooseWnd : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseWnd(QWidget *parent = nullptr);
    ~ChooseWnd();

private slots:
    void on_pButOpen_clicked();
    void set_name_to_table(QString str);
    void set_data_to_table(QVector<QString>);
    static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);
    bool loadFile(const QString &fileName);
    QString get_file_name(const QString &fileName);
    void on_pButUp_clicked();
    void on_pButDown_clicked();
    void on_pButDelete_clicked();
    void on_pButMult2_clicked();
    void on_pButDiv2_clicked();
    void slot_set_focus(int);
private:
    Ui::ChooseWnd *ui;
    ViewDataModel *model;
    QVector <QString> list_pix;
signals:
    void sig_send_pix(QString);
    void sig_del_pix(int);
    void sig_change_up(int);
    void sig_change_down(int);
    void sig_scale_mult_2();
    void sig_scale_div_2();

};

#endif // CHOOSEWND_H
