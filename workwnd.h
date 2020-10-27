#ifndef WORKWND_H
#define WORKWND_H

#include <QGraphicsScene>
#include <QPointer>
#include <QDialog>
#include <QWidget>

#include "moveitem.h"

namespace Ui {
class WorkWnd;
}

class WorkWnd : public QDialog
{
    Q_OBJECT

public:
    explicit WorkWnd(QWidget *parent = nullptr);
    ~WorkWnd();

private slots:
    void on_pButMult2_clicked();
    void on_pButDiv2_clicked();
    void slot_get_pix(QString);
    void slot_del_pix(int);
    void slot_change_up(int);
    void slot_change_down(int);
    void slot_set_focus();

private:
    Ui::WorkWnd *ui;
    QGraphicsScene *scene;
    QList <MoveItem*> vec_moveitem;
};


#endif // WORKWND_H
