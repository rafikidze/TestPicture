#ifndef CHOOSEWND_H
#define CHOOSEWND_H

#include <QDialog>

#include "browse.h"

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
    void set_way_str(QString str);

private:
    Ui::ChooseWnd *ui;
    Browse *browse;          // класс представления дерева каталогов

};

#endif // CHOOSEWND_H
