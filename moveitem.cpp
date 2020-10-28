#include "moveitem.h"

////////////////////////////////////
/// \brief MoveItem::MoveItem
/// \param parent
/// Конструктор
MoveItem::MoveItem(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}

//////////////////////////////
/// \brief MoveItem::~MoveItem
/// Деструктор
MoveItem::~MoveItem()
{

}

////////////////////////////////////////////////////////
/// \brief MoveItem::setScaledPixmap
/// \param pixmap
/// Установить картинку
void MoveItem::setScaledPixmap(const QPixmap &pixmap)
{
  m_pixmap = pixmap;
  rect_pix = QRect(-m_pixmap.rect().width()/2,
                   -m_pixmap.rect().height()/2,
                    m_pixmap.rect().width(),
                    m_pixmap.rect().height());
  update();
}


////////////////////////////////////
/// \brief MoveItem::boundingRect
/// \return
/// Переопределенная функция перерисовки элемента
QRectF MoveItem::boundingRect() const
{
   if (false == m_pixmap.isNull())
   {
       return QRectF (rect_pix);
   }
   else return QRectF (0,0,0,0);

}

///////////////////////////////
/// \brief MoveItem::resizePix
/// \param value true - увеличиваем, false - уменьшаем
/// Функция изменения размера элемента
void MoveItem::resizePix(bool value)
{
    QRect rect_temp = rect_pix;
    if(value) // mult 2
        rect_pix = QRect(rect_temp.x()*2, rect_temp.y()*2, rect_temp.width()*2, rect_temp.height()*2);

    else  // div 2
        rect_pix = QRect(rect_temp.x()/2, rect_temp.y()/2, rect_temp.width()/2, rect_temp.height()/2);
    this->update(rect_pix);
}

///////////////////////////
/// \brief MoveItem::paint
/// \param painter
/// \param option
/// \param widget
/// Отрисовка элемента в локальных координатах
void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (false == m_pixmap.isNull()) {
        painter->drawPixmap(rect_pix, m_pixmap);
     }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

///////////////////////////////////
/// \brief MoveItem::mouseMoveEvent
/// \param event
/// Устанавливает позицию графического элемента в сцене через координаты курсора
void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

////////////////////////////////////
/// \brief MoveItem::mousePressEvent
/// \param event
/// Заменяет курсор на руку при нажатии мышью на графический элемент,
/// передает сигнал о том, что был установлен фокус
void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    emit sig_setFocus();
    Q_UNUSED(event);
}

///////////////////////////////////////
/// \brief MoveItem::mouseReleaseEvent
/// \param event
/// Заменяет ркук на обычный курсор при отпускании мышью элемента
void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
