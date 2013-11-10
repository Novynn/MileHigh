#include "plane.h"
#include <QPainter>
#include <QWidget>
#include <QGraphicsScene>

Plane::Plane(double id)
    : QGraphicsObject()
    , _id(id)
    , _dirty(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void Plane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget)
    QPen pen(Qt::black);
    pen.setWidth(isSelected() ? 3 : 1);
    painter->setPen(pen);
    painter->setBrush(Qt::blue);
    painter->drawEllipse(QPointF(0, 0), _collisionRadius, _collisionRadius);
}

QRectF Plane::boundingRect() const {
    return QRectF(-(_collisionRadius/2),
                  -(_collisionRadius/2),
                  _collisionRadius*2,
                  _collisionRadius*2);
}

QPainterPath Plane::shape() const {
    QPainterPath path;
    path.addEllipse(QPointF(0, 0), _collisionRadius, _collisionRadius);
    return path;
}
