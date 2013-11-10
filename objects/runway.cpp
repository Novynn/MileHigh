#include "runway.h"
#include <QPainter>
#include <QWidget>

Runway::Runway() :
    QGraphicsRectItem()
{
}

void Runway::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget)
    painter->setBrush(Qt::darkGray);
    painter->drawRect(rect());
}
