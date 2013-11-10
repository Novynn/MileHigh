#include "obstacle.h"
#include <QPainter>
#include <QWidget>

Obstacle::Obstacle()
    : QGraphicsRectItem()
{
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget)
    painter->setPen(Qt::black);
    painter->setBrush(Qt::red);
    painter->drawRect(rect());
}
