#include "workwnd.h"
#include "ui_workwnd.h"

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

WorkWnd::WorkWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkWnd)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex); // настраиваем индексацию элементов
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(ui->graphicsView->rect()); // Устанавливаем размер сцены



}

WorkWnd::~WorkWnd()
{
  //  scene->clear();
  //  vec_moveitem.clear();
    delete scene;
    delete ui;
}

void WorkWnd::on_pButMult2_clicked()
{
    if(!vec_moveitem.isEmpty())
    {
        vec_moveitem.at(vec_moveitem.size()-1)->resizePix(true);
    }
    scene->update();
}

void WorkWnd::on_pButDiv2_clicked()
{
    if(!vec_moveitem.isEmpty())
    {
        vec_moveitem.at(vec_moveitem.size()-1)->resizePix(false);
    }
    scene->update();

}
void WorkWnd::slot_get_pix(QString name)
{
    QPixmap pix(name);
    MoveItem *item = new MoveItem();        // Создаём графический элемент
    item->setScaledPixmap(pix);
    item->setPos(randomBetween(30, 550),    // Устанавливаем случайную позицию элемента
                 randomBetween(30, 550));
    item->setZValue(scene->items().size());
    scene->addItem(item);   // Добавляем элемент на графическую сцену
    vec_moveitem.append(item);
    connect(item, &MoveItem::sig_setFocus, this, &WorkWnd::slot_set_focus);

}
void WorkWnd::slot_del_pix(int index)
{
    if(vec_moveitem.size() >= index)
    {
        scene->removeItem(vec_moveitem.at(index));
        vec_moveitem.removeAt(index);
        scene->update();
    }
}
void WorkWnd::slot_change_up(int index_)
{
    if(vec_moveitem.size() > index_)
    {
       qreal ZValue =  vec_moveitem.at(index_)->zValue();
       vec_moveitem.at(index_)->setZValue(vec_moveitem.at(index_-1)->zValue());
       vec_moveitem.at(index_-1)->setZValue(ZValue);
       vec_moveitem.move(index_, index_-1);
       scene->update();
    }

}
void WorkWnd::slot_change_down(int index_)
{
    if(vec_moveitem.size() > index_)
    {
       qreal ZValue =  vec_moveitem.at(index_)->zValue();
       vec_moveitem.at(index_)->setZValue(vec_moveitem.at(index_+1)->zValue());
       vec_moveitem.at(index_+1)->setZValue(ZValue);
       vec_moveitem.move(index_, index_+1);
       scene->update();
    }
}

void WorkWnd::slot_set_focus()
{
    qDebug() << "here";

}
