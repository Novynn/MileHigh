#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "milehigh.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MileHigh* app = new MileHigh(this);
    app->initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}
