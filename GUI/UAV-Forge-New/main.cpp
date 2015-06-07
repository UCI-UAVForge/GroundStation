#include <QApplication>
#include <QSplashScreen>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QPixmap pixmap(":/res/UAV_FORGE_LOGO_2.png");
    QSplashScreen splash(pixmap);
    splash.show();

    MainWindow x;
    x.showFullScreen();
    splash.finish(&x);

    return a.exec();
}
