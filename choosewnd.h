#ifndef CHOOSEWND_H
#define CHOOSEWND_H

#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QFileDialog>


#include <QDialog>

#include "viewdatamodel.h"

namespace Ui {
class ChooseWnd;
}

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
   /* void dragLeaveEvent(QDragLeaveEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);*/
    void on_pButUp_clicked();

    void on_pButDown_clicked();

private:
    Ui::ChooseWnd *ui;
    ViewDataModel *model;
    QVector <QString> list_pix; // возможно заменить QString сразу на QImage
signals:
 //   void keyboard(QKeyEvent *event);
 //   void dropped(const QMimeData* mimeData = 0);
  //  void moved(int old_row, int new_row);


};

#endif // CHOOSEWND_H
