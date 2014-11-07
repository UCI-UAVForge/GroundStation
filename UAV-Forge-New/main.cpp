#include "mainwindow.h"
#include <QApplication>
#include "mapplanning.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow x;
    MapPlanning w;
    w.show();
    x.show();

    return a.exec();
}
