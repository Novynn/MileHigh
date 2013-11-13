#include "mainwindow.h"
#include "milehighwidget.h"
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    QToolButton *newTabButton = new QToolButton(this);
    tabWidget->setCornerWidget(newTabButton, Qt::TopRightCorner);
    newTabButton->setText("+");
    newTabButton->setCursor(Qt::ArrowCursor);
    newTabButton->setAutoRaise(true);
    QObject::connect(newTabButton, SIGNAL(clicked()), this, SLOT(newTab()));
    newTabButton->setToolTip(tr("Add page"));

    newTab();
}

void MainWindow::newTab(){
    MileHighWidget* widget = new MileHighWidget(this);
    widget->setTableWidget(tableWidget);
    tabWidget->addTab(widget, "Tab");
}
