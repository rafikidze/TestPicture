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

    QPixmap pixmap("C:/Users/nto400.26/Pictures/4.jpg");
    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    MoveItem *item = new MoveItem();        // Создаём графический элемент
    item->setScaledPixmap(pixmap);
    item->setPos(randomBetween(30, 470),    // Устанавливаем случайную позицию элемента
                 randomBetween(30, 470));

    scene->addItem(item);   // Добавляем элемент на графическую сцену

    vec_moveitem.append(item);
}

WorkWnd::~WorkWnd()
{
    delete ui;
}


void WorkWnd::on_pButMult2_clicked()
{
    if(!vec_moveitem.isEmpty())
    {
        vec_moveitem.at(0)->resizePix(true);
    }
    scene->update();
}

void WorkWnd::on_pButDiv2_clicked()
{
    if(!vec_moveitem.isEmpty())
    {
        vec_moveitem.at(0)->resizePix(false);
    }
    scene->update();

}
