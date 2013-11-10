#include "milehigh.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsScene>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QUrlQuery>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

#include "objects/runway.h"
#include "objects/plane.h"
#include "objects/obstacle.h"

const QString MileHigh::BASE_URL       = "http://challenge.hacktivate.me:3000";
const QString MileHigh::GET_URL        = BASE_URL + "/get";
const QString MileHigh::POST_URL       = BASE_URL + "/post";
const QString MileHigh::SESSION_URL    = BASE_URL + "/new-session";

MileHigh::MileHigh(QObject *parent)
    : QGraphicsScene(parent)
    , _net(new QNetworkAccessManager(this))
    , _timer(new QTimer(this))
    , _runway(0)
{
    _token = "";
    _status = Status::IDLE;

    connect(_net, &QNetworkAccessManager::finished,
            this, &MileHigh::serverReply);
    connect(_timer, &QTimer::timeout,
            this, &MileHigh::tick);

    _timer->start(1000);
}

bool MileHigh::initialize(){
    qDebug() << "Initializing connection to the server.";
    _status = Status::INITIALIZING;
    requestToken();
    return true;
}

void MileHigh::tick(){
    if (_status == Status::INITIALIZING){
        if (!_token.isEmpty()){
            qDebug() << "Token confirmed, the application has now started.";
            _status = Status::RUNNING;
        }
    }
    if (_status == Status::RUNNING){
        // Refresh all data
        //qDebug() << "Refreshing data...";
        requestData();

        // Post all new data
        sendData();
    }

//    if (selectedItems().count() > 0){
//        qDebug() << selectedItems();
//    }
}

void MileHigh::addPlane(Plane *plane){
    _planes.insert(plane->id(), plane);
    addItem(plane);
}

void MileHigh::addObstacle(Obstacle *ob){
    addItem(ob);
}

void MileHigh::setPlanesDirty(){
    foreach(Plane* plane, _planes){
        plane->setDirty();
    }
}

/*
 *  Handling Requests
 *
 *
 *
 *
 */

void MileHigh::requestToken(){
    QNetworkRequest request;
    request.setUrl(SESSION_URL);

    _net->get(request);
}

void MileHigh::requestData(){
    QNetworkRequest request;
    request.setUrl(GET_URL + "?token=" + _token);

    _net->get(request);
}

void MileHigh::sendData(){
    QJsonArray directions;
    foreach(Plane* plane, _planes){
        if (plane->directedWaypoint().isNull()) continue;

        QJsonObject direction;
        direction.insert("plane_id", plane->id());
        QJsonObject waypoint;
        waypoint.insert("x", plane->directedWaypoint().x());
        waypoint.insert("y", plane->directedWaypoint().y());
        direction.insert("waypoint", waypoint);
        directions.append(direction);
    }
    // No data to report
    if (directions.count() == 0) return;

    QJsonObject data;
    data.insert("directions", directions);
    data.insert("token", _token);
    QJsonDocument doc;
    doc.setObject(data);

    QNetworkRequest request;
    request.setUrl(POST_URL);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    _net->post(request, doc.toJson(QJsonDocument::Compact));
}

void MileHigh::drawBackground(QPainter *painter, const QRectF &rect){
    QGraphicsScene::drawBackground(painter, rect);
    painter->setBrush(Qt::white);
    painter->drawRect(sceneRect());
}

void MileHigh::drawForeground(QPainter *painter, const QRectF &rect){
    QGraphicsScene::drawForeground(painter, rect);
    foreach(Plane* plane, _planes){
        painter->drawText(plane->scenePos().x(),
                          plane->scenePos().y(),
                          QString::number(plane->id()));
        painter->drawText(plane->scenePos().x() +40,
                          plane->scenePos().y(),
                          plane->name());
        if (plane->flightPath().isEmpty()){
            painter->setPen(Qt::yellow);

            QPainterPath _flightPath = QPainterPath(plane->scenePos());

            QLineF line(plane->scenePos(), plane->directedWaypoint());
            QLineF line2 = line.normalVector();
            line2.translate(-(line2.p1() - line.pointAt(0.5)));
            line2.setLength(line2.length() / 2);

            _flightPath.cubicTo(line2.p2(), line2.p2(), plane->directedWaypoint());
            painter->drawLine(line2);
            painter->drawPath(_flightPath);
        }
        if (!plane->waypoint().isNull()){
            painter->setPen(Qt::blue);
            painter->drawLine(plane->scenePos(), plane->waypoint());
        }
        if (!plane->directedWaypoint().isNull()){
            painter->setPen(Qt::darkBlue);
            painter->drawLine(plane->scenePos(), plane->directedWaypoint());
        }
    }
}

static QList<Plane*> selectedPlanes;
void MileHigh::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::RightButton){
        selectedPlanes.clear();
        foreach(QGraphicsItem* item, selectedItems()){
            Plane* plane = dynamic_cast<Plane*>(item);
            if (plane){
                plane->setDirectedWaypoint(event->scenePos());
            }
            selectedPlanes.append(plane);
        }
        event->accept();
    }
    QGraphicsScene::mousePressEvent(event);
}

void MileHigh::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    //QGraphicsScene::mouseReleaseEvent(event);
    foreach(Plane* plane, selectedPlanes){
        plane->setSelected(true);
    }
    selectedPlanes.clear();
}

/*
 *  Handling Replies
 *
 *
 *
 *
 */

void MileHigh::serverReply(QNetworkReply *reply){
    QNetworkRequest request = reply->request();

    if (reply->error() != QNetworkReply::NoError){
        qWarning() << "An error has occured with the server.";
        qWarning() << "> Error: " << reply->errorString();
        reply->deleteLater();
        return;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll(), &error);
    if (error.error != QJsonParseError::NoError){
        qWarning() << "An error has occured parsing the reply!";
        qWarning() << "> Error: " << error.errorString();
        reply->deleteLater();
        return;
    }

    if (request.url() == SESSION_URL){
        recievedToken(&doc);
    } else if (request.url() == GET_URL + "?token=" + _token) {
        recievedGet(&doc);
    } else if (request.url() == POST_URL){
        recievedPost(&doc);
    } else {
        qWarning() << "The server was requested with an unhandled URL.";
        qWarning() << "> Requested URL: " << request.url();
    }
    reply->deleteLater();
}

void MileHigh::recievedToken(QJsonDocument* doc){
    QString token = doc->object().value("token").toString();
    qDebug() << "Session key received: " << token;
    _token = token;
}
void MileHigh::recievedGet(QJsonDocument* doc){
    doc->object();
    //qDebug() << "Fleet data recieved.";
    //qDebug() << doc->toJson(QJsonDocument::Indented);

    // Boundary
    {
        QJsonObject boundaryData = doc->object().value("boundary").toObject();
        QJsonObject max = boundaryData.value("max").toObject();
        QJsonObject min = boundaryData.value("min").toObject();
        QRectF boundary(QPointF(min.value("x").toDouble(),
                                min.value("y").toDouble()),
                        QPointF(max.value("x").toDouble(),
                                max.value("y").toDouble()));
        setSceneRect(boundary);
        views().first()->fitInView(boundary, Qt::KeepAspectRatio);
    }

    // Runway
    {
        QJsonObject runwayData = doc->object().value("runway").toObject();
        auto x = runwayData.value("x").toDouble();
        auto y = runwayData.value("y").toDouble();

        if (_runway == 0){
            _runway = new Runway();
            addItem(_runway);
        }
        _runway->setPos(x, y);
        _runway->setRect(-32, -64, 64, 128);
    }

    // Directions
    {
        QJsonArray directionsData = doc->object().value("directions").toArray();
        _directionsDoc = QJsonDocument(directionsData);

        emit directionsDataChanged(_directionsDoc.toJson(QJsonDocument::Indented));
    }

    // Objects
    {
        // First of all, we have to clear all the obstacles and replace them
        _obstacles.clear();
        // And make all the planes dirty so we can remove them if they disappear!
        setPlanesDirty();

        QJsonArray objectsData = doc->object().value("objects").toArray();
        foreach (QJsonValue objectValue, objectsData){
            QJsonObject objectData = objectValue.toObject();
            QString type = objectData.value("type").toString().toLower();
            if (type == "plane"){
                auto id = objectData.value("id").toDouble();

                if (!_planes.contains(id)){
                    Plane* plane = Plane::fromJson(objectData);
                    addPlane(plane);
                    continue;
                }
                Plane* plane = _planes.value(id);
                if (plane != 0){
                    plane->updateData(objectData);
                }
            } else if (type == "obstacle") {
                QJsonObject boundaryData = objectData.value("boundary").toObject();
                QJsonObject min = boundaryData.value("min").toObject();
                QJsonObject max = boundaryData.value("max").toObject();
                QRectF boundary(QPointF(min.value("x").toDouble(),
                                        min.value("y").toDouble()),
                                QPointF(max.value("x").toDouble(),
                                        max.value("y").toDouble()));
                // TODO: Check if it already exists
                // TODO: Update boundary
                Obstacle* obstacle = new Obstacle();
                obstacle->setPos(boundary.topLeft());
                obstacle->setRect(boundary.normalized());
                addObstacle(obstacle);
            } else {
                qWarning() << qPrintable("> Unknown object type of [" + type + "]");
            }
        }

        // Dirty planes! :O
        foreach(Plane* plane, _planes){
            if (!plane->dirty()) continue;

            // Goodbye little plane
            _planes.remove(plane->id());
            removeItem(plane);
            delete plane;
            plane = 0;
        }
    }
}
void MileHigh::recievedPost(QJsonDocument* doc){
    //qDebug() << "Post data recieved: " << doc->toJson();
}
