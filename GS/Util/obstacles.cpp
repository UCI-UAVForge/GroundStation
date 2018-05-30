#include "obstacles.h"

Obstacles::Obstacles()
{}

Obstacles::Obstacles(QJsonObject obj)
{
    moving_obstacles = obj["moving_obstacles"].toArray();
    stationary_obstacles = obj["stationary_obstacles"].toArray();
}

//QJsonArray Obstacles::get_moving_obstacles(){
//    return moving_obstacles;
//}

void Obstacles::set_stationary_obstacles(QJsonArray arr){
    stationary_obstacles = arr;
}

QJsonArray Obstacles::get_stationary_obstacles(){
    return stationary_obstacles;
}

QJsonObject Obstacles::get_obj(){
    QJsonObject obj;
    obj["Obstacles"]=stationary_obstacles;
    return obj;
}

// https://math.stackexchange.com/a/980131
bool Obstacles::segmentIntersectsObstacles(Point a, Point b) {
    for (QJsonValueRef o : stationary_obstacles) {
        QJsonObject obstacle = o.toObject();
        Point cyl_center = Point::fromGeodetic(obstacle["latitude"].toDouble(), obstacle["longitude"].toDouble(), 0);
        qInfo() << "obstacle: " << cyl_center.toGeodetic();
        double radius = obstacle["cylinder_radius"].toDouble();
        // ignore the z-axis for now
        double x_min = fmin(a.x, b.x);
        double x_max = fmax(a.x, b.x);
        double y_min = fmin(a.y, b.y);
        double y_max = fmax(a.y, b.y);
        double rsqr = pow(radius, 2);
        for (double x = x_min; x < x_max; x += 30) {
            double xsqr = pow(x - cyl_center.x, 2);
            for (double y = y_min; y < y_max; y += 30) {
                if (xsqr + pow(y - cyl_center.y, 2) < rsqr) {
                    // should check z and cylinder height
                    return true;
                }
            }
        }

//        if (pow(cyl_center.x, 2) + pow(slope * cyl_center.x + offset, 2) == pow(radius, 2)) {
//            // treating cyllinder as infinite height, we should be checking z here
//            return true;
//        }
    }

    return false;
}

