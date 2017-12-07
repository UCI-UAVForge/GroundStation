#include <QApplication>
#include <QSplashScreen>
#include <QtSvg>

#include "maindockwindow.h"
#include "voronoi-mdp.hpp"

int main(int argc, char *argv[]) {

    static const int splash_width = 600;
    static const int splash_height = 217;
    static const QString filename(":/res/images/UAV Forge Logo 2015.svg");

    QApplication a(argc, argv);
    //Construct and load the SVG image
    QSvgRenderer svg(filename);
    //Calculate the scaled size within a bounded size
    QSize SplashSize = svg.viewBox().size();
    SplashSize.scale(splash_width, splash_height, Qt::KeepAspectRatio);
    //Construct the pixmap to contain the SVG image
    QPixmap pixmap(SplashSize);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    //Render the SVG to the pixmap
    svg.render(&painter, pixmap.rect());
    //Construct and show the splash screen
    QSplashScreen splash(pixmap);
    // splash.show();
    gen_path(std::vector<Point>{Point{1,1,1}, Point{1,1,1}, Point{3,3,3}}, std::vector<Obstacles>());

//    MainMDIDisplay x;
    MainDockWindow dockWindow;
    //x.showNormal();
    dockWindow.showNormal();
    //Hide the splash screen.
    splash.finish(&dockWindow);

    return a.exec();
}

