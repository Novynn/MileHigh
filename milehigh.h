#ifndef MILEHIGH_H
#define MILEHIGH_H

#include <QByteArray>
#include <QGraphicsScene>
#include <QDebug>
#include <QMap>
#include <QList>
class QTimer;
class QNetworkAccessManager;
class QNetworkReply;
class Obstacle;
class Plane;

class MileHigh : public QGraphicsScene
{
public:
    MileHigh(QObject* parent = 0);

    enum class Status {
        IDLE,
        INITIALIZING,
        RUNNING,
        TERMINATING
    };

    bool initialize();

    static const QString BASE_URL;
    static const QString GET_URL;
    static const QString POST_URL;
    static const QString SESSION_URL;

    void requestToken();
    void requestData();
    void sendData();

    QString token(){
        return _token;
    }
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

    QList<Obstacle*> _obstacles;
    QMap<int, Plane*> _planes;

private slots:
    void tick();
    void serverReply(QNetworkReply*);
};

#endif // MILEHIGH_H
