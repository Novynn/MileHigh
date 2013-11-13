#ifndef MILEHIGHWIDGET_H
#define MILEHIGHWIDGET_H

#include <QWidget>
#include <QTreeWidget>
class MileHigh;
class QGraphicsView;
class QTreeWidgetItem;

class MileHighWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MileHighWidget(QWidget *parent = 0);
public slots:
    void sceneUpdated();
protected:
    void resizeEvent(QResizeEvent *event);
    void update();
private slots:
    void boundaryUpdate();
private:
    QTreeWidget* _treeWidget;
    QGraphicsView* _view;
    MileHigh* _app;

    QTreeWidgetItem* _planesItem;
    QTreeWidgetItem* _boundariesItem;
    QMap<int, QTreeWidgetItem*> _planeWidgets;
};

#endif // MILEHIGHWIDGET_H
