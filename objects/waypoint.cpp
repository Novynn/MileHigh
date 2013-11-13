#include "waypoint.h"
#include <QPainter>
#include <QWidget>
#include <QDebug>

QList<Waypoint*> Waypoint::_allWaypoints;

Waypoint::Waypoint()
    : QGraphicsItem()
    , _available(true)
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

void Waypoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget)
//    Q_UNUSED(option)

//    if (available()){
//        painter->setOpacity(0.5);
//        painter->setBrush(Qt::yellow);
//        painter->setPen(Qt::transparent);
//        painter->drawRect(boundingRect());
//        painter->setOpacity(1.0);
//    }
//    else {
//        painter->setBrush(Qt::red);
//    }
//    painter->setPen(Qt::black);
//    if (available()){
//        foreach(Waypoint* connected, waypoints()){
//            if (!connected) continue;
//            if (connected->available()){
//                painter->drawLine(scenePos(), connected->scenePos());
//            }
//        }
//    }
//    int radius = 5;
//    painter->drawEllipse(0, 0, radius, radius);
}

QRectF Waypoint::boundingRect() const {
    return QRectF(-4,
                  -4,
                  8,
                  8);
}

QPainterPath Waypoint::shape() const {
    QPainterPath path;
    path.addEllipse(QPointF(0, 0), 20, 20);
    return path;
}
