#include "mainwindow.h"
#include <QGraphicsView>
#include "milehigh.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    QGraphicsView* view = new QGraphicsView(this);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    MileHigh* app = new MileHigh(view);
    view->setScene(app);
    app->initialize();

    centralWidget()->layout()->addWidget(view);
}

void MainWindow::newTab(){
//    QDockWidget* widget = new QDockWidget("Tab");


//    QGraphicsView* view = new QGraphicsView(widget);
//    view->setDragMode(QGraphicsView::RubberBandDrag);
//    MileHigh* app = new MileHigh(view);
//    view->setScene(app);
//    app->initialize();

//    widget->setWidget(view);
//    addDockWidget(Qt::LeftDockWidgetArea, widget);
//    tabifyDockWidget(tabWidget, widget);
}

void MainWindow::on_pushButton_clicked()
{
    newTab();
}
