#ifndef WORKWND_H
#define WORKWND_H

#include <QGraphicsScene>
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

private:
    Ui::WorkWnd *ui;
    QGraphicsScene *scene;
    QVector <MoveItem*> vec_moveitem;
};


#endif // WORKWND_H
