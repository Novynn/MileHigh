#include "milehighwidget.h"
#include "milehigh.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsView>
#include <QToolButton>
#include <QLayout>
#include <QSplitter>
#include <QQueue>


MileHighWidget::MileHighWidget(QWidget *parent)
    : QWidget(parent)
    , _treeWidget(new QTreeWidget(this))
    , _view(new QGraphicsView(this))
    , _app(new MileHigh(_view))
{
    QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(_view);
    splitter->addWidget(_treeWidget);
    QList<int> sizes;
    sizes << splitter->height();
    sizes << splitter->width() - splitter->height();
    splitter->setSizes(sizes);
    setLayout(new QHBoxLayout(this));
    layout()->setMargin(0);
    layout()->addWidget(splitter);
    _view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    _view->setDragMode(QGraphicsView::RubberBandDrag);
    _view->setScene(_app);

    connect(_app, SIGNAL(sceneRectChanged(QRectF)), this, SLOT(boundaryUpdate()));
    connect(splitter, SIGNAL(splitterMoved(int,int)), this, SLOT(boundaryUpdate()));

    connect(_app, SIGNAL(updated()), this, SLOT(sceneUpdated()));

    _app->initialize();

    _treeWidget->setHeaderLabel("Current Data");

}

void MileHighWidget::sceneUpdated(){
//    QJsonDocument data = _app->currentData();
//    QQueue<QJsonObject> objectQueue;
//    objectQueue.enqueue(data.object());
//    bool top = true;
//    while(!objectQueue.isEmpty()){
//        QJsonObject object = objectQueue.dequeue();
//        foreach(QString key, object->keys()){
//            QJsonValue child = object->value(key);
//            if (child.isObject()){
//                QJsonObject childObject = child.toObject();
//                objectQueue.enqueue(childObject);
//            }
//            QTreeWidgetItem* item = new QTreeWidgetItem(_treeWidget);

//        }
//        top = false;
//    }

}

void MileHighWidget::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    boundaryUpdate();
}

void MileHighWidget::boundaryUpdate(){
    _view->fitInView(_app->sceneRect(), Qt::KeepAspectRatio);
}
