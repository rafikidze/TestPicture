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
    vec_moveitem.clear();
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

    qDebug() << name <<  scene->items().first()->zValue();
    vec_moveitem.append(item);

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

    for(int t = 0; t < scene->items().size(); t++)
    {
        qDebug() << scene->items().at(t)->zValue();
    }


    if(scene->items().size() > index_)
    {
       int index = scene->items().size() - index_;
       qreal ZValue = scene->items().at(index)->zValue();

          qDebug() << "ZValue1:" << ZValue << "index1:" << index
                   << "ZValue2:" << scene->items().at(index-1)->zValue() << "index2:" << index-1   ;

       scene->items().at(index)->setZValue(scene->items().at(index-1)->zValue());

       qDebug() << "new ZValue index:" << scene->items().at(index)->zValue();

       scene->items().at(index-1)->setZValue(ZValue);
       qDebug() << "new ZValue index-1:" << scene->items().at(index-1)->zValue();


       vec_moveitem.move(index, index-1);
       scene->items().move(index, index-1);
       scene->update();



    }

}
void WorkWnd::slot_change_down(int index_)
{
    if(scene->items().size() > index_)
    {
       int index = scene->items().size() - index_;
       qreal ZValue = scene->items().at(index)->zValue();
       scene->items().at(index)->setZValue(scene->items().at(index-1)->zValue());
       scene->items().at(index+1)->setZValue(ZValue);
       vec_moveitem.move(index, index+1);
       scene->items().move(index, index+1);
       scene->update();
    }

}

