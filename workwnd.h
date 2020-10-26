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

private:
    Ui::WorkWnd *ui;
    QGraphicsScene *scene;
};


#endif // WORKWND_H
