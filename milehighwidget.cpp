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
#include <QPushButton>
#include <QTableWidgetItem>
#include "objects/plane.h"

MileHighWidget::MileHighWidget(QWidget *parent)
    : QWidget(parent)
    , _textWidget(new QTextEdit(this))
    , _view(new QGraphicsView(this))
    , _app(new MileHigh(_view))
{
    QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(_view);
    QWidget* widget = new QWidget(this);
    QPushButton* button = new QPushButton("Regenerate Waypoints", widget);
    widget->setLayout(new QVBoxLayout(this));
    widget->layout()->addWidget(_textWidget);
    widget->layout()->addWidget(button);
    splitter->addWidget(widget);
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

    connect(button, SIGNAL(clicked()), this, SLOT(buttonPushed()));

    connect(_app, SIGNAL(sceneRectChanged(QRectF)), this, SLOT(boundaryUpdate()));
    connect(splitter, SIGNAL(splitterMoved(int,int)), this, SLOT(boundaryUpdate()));

    connect(_app, SIGNAL(updated()), this, SLOT(sceneUpdated()));

    _app->initialize();
}

void MileHighWidget::buttonPushed(){
    _app->regenerateWaypoints();
}

void MileHighWidget::sceneUpdated(){
    _textWidget->setText(_app->currentData().toJson(QJsonDocument::Indented));
    _tableWidget->clear();
    int row = 0;
    foreach(Plane* plane, _app->planes().values()){
        QTableWidgetItem* item = new QTableWidgetItem(plane->name());
        _tableWidget->setItem(row, 0, item);
        item = new QTableWidgetItem(QString::number(plane->fuel()));
        _tableWidget->setItem(row, 1, item);
        row++;
    }
}

void MileHighWidget::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    boundaryUpdate();
}

void MileHighWidget::boundaryUpdate(){
    _view->fitInView(_app->sceneRect(), Qt::KeepAspectRatio);
}
