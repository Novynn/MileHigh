#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentMSecsSinceEpoch());
    MainWindow w;
    w.show();

    return a.exec();
}
