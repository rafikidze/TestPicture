#include "moveitem.h"

MoveItem::MoveItem(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

MoveItem::~MoveItem()
{

}
void MoveItem::setScaledPixmap(const QPixmap &pixmap)
{
  m_pixmap = pixmap;
  rect_pix = QRect(-m_pixmap.rect().width()/2,
                   -m_pixmap.rect().height()/2,
                    m_pixmap.rect().width(),
                    m_pixmap.rect().height());
  update();
}

QRectF MoveItem::boundingRect() const
{
   if (false == m_pixmap.isNull())
   {
       return QRectF (rect_pix);
   }
   else return QRectF (0,0,0,0);

}
void MoveItem::resizePix(bool value)
{
    QRect rect_temp = rect_pix;
    if(value) // more
        rect_pix = QRect(rect_temp.x()*2, rect_temp.y()*2, rect_temp.width()*2, rect_temp.height()*2);

    else  // less
        rect_pix = QRect(rect_temp.x()/2, rect_temp.y()/2, rect_temp.width()/2, rect_temp.height()/2);

    this->update(rect_pix);
}
void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (false == m_pixmap.isNull()) {
        painter->drawPixmap(rect_pix, m_pixmap);
     }


  /*  QSize widgetSize = m_pixmap.size();

    qDebug() << widgetSize;

    //QPixmap scaledPixmap = m_pixmap.scaled(widgetSize, Qt::KeepAspectRatio);
   // QPoint center((widgetSize.width() - scaledPixmap.width())/2,
   //               (widgetSize.height() - scaledPixmap.height())/2);
    QPoint p(0,0);
    painter->drawPixmap(p, m_pixmap);

    if (false == m_pixmap.isNull()) {
          QSize widgetSize = m_pixmap.size();
          QPixmap scaledPixmap = m_pixmap.scaled(widgetSize, Qt::KeepAspectRatio);
          QPoint center((widgetSize.width() - scaledPixmap.width())/2,
                        (widgetSize.height() - scaledPixmap.height())/2);
          painter->drawPixmap(center, scaledPixmap);
        }*/



    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   //  Устанавливаем позицию графического элемента
   //  в графической сцене, транслировав координаты
   //  курсора внутри графического элемента
   //  в координатную систему графической сцены
    this->setPos(mapToScene(event->pos()));

}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // При нажатии мышью на графический элемент
    // заменяем курсор на руку, которая держит этот элемента
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // При отпускании мышью элемента
    // заменяем на обычный курсор стрелку
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
