#ifndef RUNWAY_H
#define RUNWAY_H

#include <QGraphicsRectItem>

class Runway : public QGraphicsRectItem
{
public:
    explicit Runway();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // RUNWAY_H
