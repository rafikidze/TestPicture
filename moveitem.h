#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class MoveItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MoveItem(QObject *parent = 0);
    ~MoveItem();
    void setScaledPixmap(const QPixmap &pixmap);
    void resizePix(bool);
private:
    QPixmap m_pixmap;
    QRect rect_pix;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void sig_setFocus();

public slots:
};

#endif // MOVEITEM_H
