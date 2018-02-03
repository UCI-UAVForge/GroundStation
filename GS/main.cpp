#include <QApplication>
#include <QSplashScreen>
#include <QtSvg>

#include "maindockwindow.h"

#include "plan_mission.hpp"
#include "point.hpp"
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
    pm.add_goal_point(Point::fromGeodetic(38.14254, -76.43409, 0));
    pm.add_goal_point(Point::fromGeodetic(38.14468, -76.42799, 0));
    QString sb ="{"
                "    \"moving_obstacles\": ["
                "        {"
                "            \"altitude_msl\": 189.56748784643966,"
                "            \"latitude\": 34.141826869853645,"
                "            \"longitude\": -76.43199876559223,"
                "            \"sphere_radius\": 150.0"
                "        },"
                "        {"
                "            \"altitude_msl\": 250.0,"
                "            \"latitude\": 34.14923628783763,"
                "            \"longitude\": -76.43238529543882,"
                "            \"sphere_radius\": 150.0"
                "        }"
                "    ],"
                "    \"stationary_obstacles\": ["
                "        {"
                "            \"cylinder_height\": 750.0,"
                "            \"cylinder_radius\": 100.0,"
                "            \"latitude\": 18.143,"
                "            \"longitude\":  -76.433"

                "        },"
                "        {"
                "            \"cylinder_height\": 400.0,"
                "            \"cylinder_radius\": 50.0,"
                "            \"latitude\": 18.149156,"
                "            \"longitude\": -76.430622"
                "        }"
                "    ]"
                "}";
    pm.set_obstacles(QJsonDocument::fromJson(sb.toUtf8()));
    //qDebug() << pm.get_path(Point::fromGeodetic(38.14468, -76.42799, 0));
//    MainMDIDisplay x;
    MainDockWindow dockWindow;
    //x.showNormal();
    dockWindow.showNormal();
    //Hide the splash screen.
    splash.finish(&dockWindow);

    return a.exec();
}

