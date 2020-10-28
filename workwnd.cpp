#include "workwnd.h"
#include "ui_workwnd.h"

////////////////////////
/// \brief randomBetween
/// \param low - минимальное число
/// \param high - максимальное число
/// \return
/// Функция для получения рандомного числа в диапазоне от low до high

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

////////////////////////////
/// \brief WorkWnd::WorkWnd
/// \param parent
/// Конструктор
WorkWnd::WorkWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkWnd)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);                   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов
    ui->graphicsView->setScene(scene);                  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);        // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

////////////////////////////
/// \brief WorkWnd::~WorkWnd
/// Деструктор
WorkWnd::~WorkWnd()
{
    scene->clear();
    vec_moveitem.clear();
    delete scene;
    delete ui;
}

/////////////////////////////////////////
/// \brief WorkWnd::on_pButMult2_clicked
/// Функция увеличения размера картинки в 2 раза
void WorkWnd::on_pButMult2_clicked()
{
    if(!vec_moveitem.isEmpty())
    {
        vec_moveitem.at(vec_moveitem.size()-1)->resizePix(true);
    }
    scene->update();
}

///////////////////////////////////////
/// \brief WorkWnd::on_pButDiv2_clicked
/// Функция уменьшения размера картинки в 2 раза
void WorkWnd::on_pButDiv2_clicked()
{
    if(!vec_moveitem.isEmpty())
    {
        vec_moveitem.at(vec_moveitem.size()-1)->resizePix(false);
    }
    scene->update();

}

////////////////////////////////////////
/// \brief WorkWnd::slot_get_pix
/// \param name
/// Функция создания графического элемента и отображение его на сцене
void WorkWnd::slot_get_pix(QString name)
{
    QPixmap pix(name);
    QPointer<MoveItem> item = new MoveItem();  // Создаём графический элемент
    item->setScaledPixmap(pix);
    item->setPos(randomBetween(30, 550),       // Устанавливаем случайную позицию элемента
                 randomBetween(30, 550));
    item->setZValue(scene->items().size());
    scene->addItem(item);   // Добавляем элемент на графическую сцену
    vec_moveitem.append(item);
    connect(item, &MoveItem::sig_setFocus, this, &WorkWnd::slot_set_focus);

}

////////////////////////////////////
/// \brief WorkWnd::slot_del_pix
/// \param index - индекс картинки
/// Удаление картинки с рабочего окна по индексу
void WorkWnd::slot_del_pix(int index)
{
    if(vec_moveitem.size() > index)
    {
        scene->removeItem(vec_moveitem.at(index));
        vec_moveitem.removeAt(index);
        scene->update();
    }
}

///////////////////////////////////////
/// \brief WorkWnd::slot_change_up
/// \param index - индекс картинки
/// Перестить картинку вперед
void WorkWnd::slot_change_up(int index)
{
    if(vec_moveitem.size() > index)
    {
       qreal ZValue =  vec_moveitem.at(index)->zValue();
       vec_moveitem.at(index)->setZValue(vec_moveitem.at(index-1)->zValue());
       vec_moveitem.at(index-1)->setZValue(ZValue);
       vec_moveitem.move(index, index-1);
       scene->items().move(index, index-1);
       scene->update();
    }

}

////////////////////////////////////////
/// \brief WorkWnd::slot_change_down
/// \param index - индекс картинки
/// Переместить картинку назад
void WorkWnd::slot_change_down(int index)
{
    if(vec_moveitem.size() > index)
    {
       qreal ZValue =  vec_moveitem.at(index)->zValue();
       vec_moveitem.at(index)->setZValue(vec_moveitem.at(index+1)->zValue());
       vec_moveitem.at(index+1)->setZValue(ZValue);
       vec_moveitem.move(index, index+1);
       scene->items().move(index, index+1);
       scene->update();
    }
}

/////////////////////////////////
/// \brief WorkWnd::slot_set_focus
/// Функция опеределения на каком элементе фокус и перемещение элемента
/// вперед, если он там не был
void WorkWnd::slot_set_focus()
{
    int index = scene->focusItem()->zValue();
    if(index == (vec_moveitem.size()-1)); // все на месте
    else {
        emit sig_send_focus(index);
        vec_moveitem.move(index, vec_moveitem.size()-1);
        for (int i = index; i < vec_moveitem.size(); i++)
            vec_moveitem.at(i)->setZValue(i);
    }
}






