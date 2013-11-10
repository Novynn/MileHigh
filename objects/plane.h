#ifndef PLANE_H
#define PLANE_H

#include <QGraphicsObject>
#include <QJsonObject>

class Plane : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Plane(double id);

    double id() const {
        return _id;
    }

    QPointF waypoint() const {
        return _waypoint;
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
        auto rotation = objectData.value("rotation").toDouble();
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

    bool _dirty;
signals:

public slots:

};

#endif // PLANE_H
