/* The main class used to initialize the program when launched by the user.
 * This class creates the MainWindow object needed for the user to utilize the
 * rest of the program.
 *
 * File added sometime prior to April 30 2015.
 */

#include <QApplication>
#include "mainwindow.h"
#include "mapplanning.h"
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

    //x.showMaximized();  //Personally, I like this one better  :P

    splash.finish(&x);


    return a.exec();
}
