#include "plane.h"
#include <QPainter>
#include <QWidget>

Plane::Plane(double id)
    : QGraphicsObject()
    , _id(id)
    , _dirty(false)
{
}

void Plane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget)
    painter->setPen(Qt::black);
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
