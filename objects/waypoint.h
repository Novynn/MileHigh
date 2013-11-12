#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QGraphicsItem>
#include <QDebug>
#include "qmath.h"

class Waypoint : public QGraphicsItem
{
public:
    explicit Waypoint();
public:
    static Waypoint* create(qreal x, qreal y){
        Waypoint* waypoint = new Waypoint();
        waypoint->setPos(x, y);
        _allWaypoints.append(waypoint);
        return waypoint;
    }

    static Waypoint* nearest(qreal rx, qreal ry){
        QLineF bestLine;
        Waypoint* bestWaypoint = 0;
        foreach(Waypoint* waypoint, _allWaypoints){
            QLineF line(QPointF(rx, ry), waypoint->pos());
            if (line.length() < bestLine.length() || bestLine.isNull()){
                bestLine = line;
                bestWaypoint = waypoint;
            }
        }
        return bestWaypoint;
    }
    static Waypoint* nearest(QPointF point){
        return nearest(point.x(), point.y());
    }
    static QList<Waypoint*> all(){
        return _allWaypoints;
    }

    void connect(Waypoint* other){
        if (_waypoints.contains(other)) return;
        _waypoints.append(other);
        other->connect(this);
    }
    bool isConnected(Waypoint* other){
        return (_waypoints.contains(other));
    }
    void disconnect(Waypoint* other){
        if (!_waypoints.contains(other)) return;
        _waypoints.removeAll(other);
        other->disconnect(this);
    }
    void disconnectAll(){
        _waypoints.clear();
    }

    QList<Waypoint*> waypoints(){
        return _waypoints;
    }

    bool available(){
        return _available;
    }

    void setAvailable(bool available = true){
        _available = available;
    }
    QRectF boundingRect() const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPainterPath shape() const;
private:
    static QList<Waypoint*> _allWaypoints;

    QList<Waypoint*> _waypoints;
    bool _available;
    int _x;
    int _y;
};

#endif // WAYPOINT_H
