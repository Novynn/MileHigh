#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsRectItem>

class Obstacle : public QGraphicsRectItem
{
public:
    explicit Obstacle();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // OBSTACLE_H
