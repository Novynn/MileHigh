#include "waypoint.h"
#include <QPainter>
#include <QWidget>
#include <QDebug>

QList<Waypoint*> Waypoint::_allWaypoints;

Waypoint::Waypoint()
    : QGraphicsItem()
    , _available(true)
{
}

void Waypoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget)
    Q_UNUSED(option)
    Q_UNUSED(painter)
}

QRectF Waypoint::boundingRect() const {
    return QRectF(scenePos().x() - 4,
                  scenePos().y() - 4,
                  8,
                  8);
}

QPainterPath Waypoint::shape() const {
    QPainterPath path;
    path.addEllipse(scenePos(), 5, 5);
    return path;
}
