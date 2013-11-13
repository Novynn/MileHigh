#ifndef MILEHIGHWIDGET_H
#define MILEHIGHWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QTableWidget>
class MileHigh;
class QGraphicsView;
class QTreeWidgetItem;

class MileHighWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MileHighWidget(QWidget *parent = 0);

    void setTableWidget(QTableWidget* widget){
        _tableWidget = widget;
    }

    QTableWidget* tableWidget(){
        return _tableWidget;
    }

public slots:
    void sceneUpdated();
protected:
    void resizeEvent(QResizeEvent *event);
    void update();
private slots:
    void boundaryUpdate();
    void buttonPushed();
private:
    QTextEdit* _textWidget;
    QGraphicsView* _view;
    MileHigh* _app;
    QTableWidget* _tableWidget;

    QTreeWidgetItem* _planesItem;
    QTreeWidgetItem* _boundariesItem;
    QMap<int, QTreeWidgetItem*> _planeWidgets;
};

#endif // MILEHIGHWIDGET_H
