#include "mainwindow.h"
#include <QApplication>
#include "mapplanning.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/res/UAV_FORGE_LOGO_2.png");
    QSplashScreen splash(pixmap);
    splash.show();
    MainWindow x;
    x.showFullScreen();
    return a.exec();
}
