#ifndef MILEHIGH_H
#define MILEHIGH_H

#include <QByteArray>
#include <QGraphicsScene>
#include <QDebug>
#include <QMap>
#include <QList>
#include <QJsonDocument>
class QTimer;
class QNetworkAccessManager;
class QNetworkReply;
class Obstacle;
class Plane;
class Runway;
class Waypoint;

class MileHigh : public QGraphicsScene
{
    Q_OBJECT
public:
    MileHigh(QObject* parent = 0);

    static const QString STATIC_TOKEN;

    enum class Status {
        IDLE,
        INITIALIZING,
        RUNNING,
        TERMINATING
    };

    QMap<int, Plane*> planes(){
        return _planes;
    }

    bool initialize();

    static const QString BASE_URL;
    static const QString GET_URL;
    static const QString POST_URL;
    static const QString SESSION_URL;

    void requestToken();
    void requestData();
    void sendData();


    void generateWaypoints();
    void regenerateWaypoints();

    QString token(){
        return _token;
    }

    QJsonDocument currentData() const {
        return _currentData;
    }
    void updatePlanes();
    void spawnWaypoint(QPointF pos, int direction, Waypoint *parent);
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void drawForeground(QPainter *painter, const QRectF &rect);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QNetworkAccessManager* _net;
    QTimer* _timer;

    QString _token;
    Status _status;

    void recievedToken(QJsonDocument* doc);
    void recievedGet(QJsonDocument* doc);
    void recievedPost(QJsonDocument* doc);

    void addPlane(Plane* plane);
    void addObstacle(Obstacle* ob);

    void setPlanesDirty();

    QJsonDocument _currentData;

    Runway* _runway;
    Waypoint* _runwayWaypoint;
    Waypoint* _landWaypoint;
    QList<Obstacle*> _obstacles;
    QMap<int, Plane*> _planes;

private slots:
    void tick();
    void serverReply(QNetworkReply*);
signals:
    void updated();
};

#endif // MILEHIGH_H
