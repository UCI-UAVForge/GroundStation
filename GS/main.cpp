#include <QApplication>
#include <QSplashScreen>
#include <QtSvg>

#include "maindockwindow.h"

#include "plan_mission.hpp"
#include "point.hpp"
Point toECEF(double lat, double lon, double alt) {
    // WGS84 ellipsoid constants:
    double a = 6378.137;
    double e = 8.1819190842622e-2;
    // prime vertical radius of curvature
    double N = a / sqrt(1 - pow(e, 2) * pow(sin(lat), 2));

    double x = (N+alt) * cos(lat) * cos(lon);
    double y = (N+alt) * cos(lat) * sin(lon);
    double z = ((1-pow(e,2)) * N + alt) * sin(lat);
    return Point{x, y, z};
}
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
    PlanMission pm;
    pm.add_goal_point(toECEF(38.143, -76.43199876559223, 189.56748784643966));
    pm.add_goal_point(toECEF(38.142, -76.43199876559223, 189.56748784643966));
    QString sb = "{"
                 "    \"moving_obstacles\": ["
                 "        {"
                 "            \"altitude_msl\": 189.56748784643966,"
                 "            \"latitude\": 38.141826869853645,"
                 "            \"longitude\": -76.43199876559223,"
                 "            \"sphere_radius\": 150.0"
                 "        },"
                 "        {"
                 "            \"altitude_msl\": 250.0,"
                 "            \"latitude\": 38.14923628783763,"
                 "            \"longitude\": -76.43238529543882,"
                 "            \"sphere_radius\": 150.0"
                 "        }"
                 "    ],"
                 "    \"stationary_obstacles\": ["
                 "        {"
                 "            \"cylinder_height\": 750.0,"
                 "            \"cylinder_radius\": 300.0,"
                 "            \"latitude\": 38.141826869853645,"
                 "            \"longitude\": -76.43199876559223"
                 "        },"
                 "        {"
                 "            \"cylinder_height\": 400.0,"
                 "            \"cylinder_radius\": 100.0,"
                 "            \"latitude\": 38.149156,"
                 "            \"longitude\": -76.430622"
                 "        }"
                 "    ]"
                 "}";
    pm.set_obstacles(QJsonDocument::fromJson(sb.toUtf8()));
    pm.get_path(toECEF(38.141, -76.43199876559223, 189.56748784643966));
//    MainMDIDisplay x;
    MainDockWindow dockWindow;
    //x.showNormal();
    dockWindow.showNormal();
    //Hide the splash screen.
    splash.finish(&dockWindow);

    return a.exec();
}

