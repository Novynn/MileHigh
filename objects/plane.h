#ifndef PLANE_H
#define PLANE_H

#include <QGraphicsItem>
#include <QJsonObject>
#include "qmath.h"

class Plane : public QGraphicsItem
{
public:
    explicit Plane(double id);

    double id() const {
        return _id;
    }

    QString name() const {
        return _name;
    }

    void setWaypoint(QPointF waypoint) {
        _waypoint = waypoint;
    }

    void setDirectedWaypoint(QPointF directedWaypoint){
        _directedWaypoint = directedWaypoint;
        // Here we have to figure out a flight path (well not here later, but here for now)
//        _flightPath = QPainterPath(scenePos());

//        QLineF line(scenePos(), _directedWaypoint);
//        QLineF line2 = line.normalVector();
//        line2.translate(line.pointAt(0.5));
//        line2.setLength(40);

//        _flightPath.cubicTo(line2.p2(), line2.p2(), _directedWaypoint);
    }

    QPointF waypoint() const {
        return _waypoint;
    }

    QPointF directedWaypoint() const {
        return _directedWaypoint;
    }

    void updateData(QJsonObject objectData){
        _name = objectData.value("name").toString();
        _penalty = objectData.value("penalty").toDouble();
        _points = objectData.value("points").toDouble();
        _speed = objectData.value("speed").toDouble();
        _turnSpeed = objectData.value("turn_speed").toDouble();
        _fuel = objectData.value("fuel").toDouble();
        _collisionRadius = objectData.value("collision_radius").toDouble();
        _graphicFile = objectData.value("graphic").toString();
        _graphicPath = objectData.value("graphic_full_path").toString();
        QJsonObject waypointData = objectData.value("waypoint").toObject();

        _waypoint = QPointF(waypointData.value("x").toDouble(), waypointData.value("y").toDouble());

        QJsonObject positionData = objectData.value("position").toObject();
        QPointF position(positionData.value("x").toDouble(),
                         positionData.value("y").toDouble());
        setPos(position);
        // Rotation needs a fix
        auto rotation = objectData.value("rotation").toDouble() - 90.0f;
        setRotation(rotation);

        _dirty = false;
    }

    static Plane* fromJson(QJsonObject objectData){
        double id = objectData.value("id").toDouble();
        Plane* plane = new Plane(id);
        plane->updateData(objectData);
        return plane;
    }

    bool dirty() const {
        return _dirty;
    }
    void setDirty(bool dirty = true){
        _dirty = dirty;
    }

    QPainterPath flightPath() const {
        return _flightPath;
    }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
private:
    double _id;
    QString _name;
    double _penalty;
    double _points;
    double _speed;
    double _turnSpeed;
    double _fuel;
    double _collisionRadius;
    QString _graphicFile;
    QString _graphicPath;
    QPointF _waypoint;
    QPointF _directedWaypoint;

    QPainterPath _flightPath;

    bool _dirty;
};

#endif // PLANE_H
