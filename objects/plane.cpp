#include "plane.h"
#include <QPainter>
#include <QWidget>
#include <QGraphicsScene>
#include <qmath.h>

Plane::Plane(double id)
    : QGraphicsItem()
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

    auto distance = _collisionRadius;
    auto angle = rotation();

    const qreal DEGTORAD = M_PI/180;
    qreal x1 = distance * 0.7 * qCos(angle * DEGTORAD);
    qreal y1 = distance * 0.7 * qSin(angle * DEGTORAD);
    qreal x2 = distance * qCos(angle * DEGTORAD);
    qreal y2 = distance * qSin(angle * DEGTORAD);

    painter->drawLine(QPointF(x1, y1), QPointF(x2, y2));
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
