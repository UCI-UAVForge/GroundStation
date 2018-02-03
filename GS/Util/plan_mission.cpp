#include "plan_mission.hpp"
#include <stack>
#include <memory>
#include <rrt/2dplane/GridStateSpace.hpp>
#include <rrt/2dplane/2dplane.hpp>
#include <rrt/BiRRT.hpp>
#include <rrt/planning/Path.hpp>
#include <Eigen/src/Core/Matrix.h>
double meters_to_deg(double meters, double latitude)
{
    return meters / (111.32 * 1000 * cos(latitude * (M_PI / 180)));
}
double SCALE_CONSTANT = 1000;
std::vector<std::pair<double, double>> PlanMission::pathfind(double start_lat, double start_lon, double end_lat, double end_lon, Obstacles obstacles) {
    qInfo() << "we in the matrix";
    int dimensions = 2;

    Eigen::Vector2d size(90000,90000);
    std::vector<Eigen::Vector2d> _previousSolution;

    std::shared_ptr<RRT::GridStateSpace> _stateSpace(new RRT::GridStateSpace(size.x(), size.y(), 20, 20));
    std::shared_ptr<RRT::BiRRT<Eigen::Vector2d>> _biRRT = std::make_shared<RRT::BiRRT<Eigen::Vector2d>>(_stateSpace, RRT::hash, dimensions);

    auto _waypointCacheMaxSize = 15;

    Eigen::Vector2d _startPos = Eigen::Vector2d(start_lat*SCALE_CONSTANT, abs(start_lon)*SCALE_CONSTANT);
    Eigen::Vector2d _goalPos = Eigen::Vector2d(end_lat*SCALE_CONSTANT, abs(end_lon)*SCALE_CONSTANT);
//    Eigen::Vector2d _startPos = Eigen::Vector2d(1, 1);
//    Eigen::Vector2d _goalPos = Eigen::Vector2d(30, 30);
    qInfo() << _startPos.x() << " " << _startPos.y();
    qInfo() << _goalPos.x() << " " << _goalPos.y();
    //  setup birrt
    _biRRT->setStartState(_startPos);
    _biRRT->setGoalState(_goalPos);
    _biRRT->setMaxStepSize(10);
    _biRRT->setGoalMaxDist(.1);

    // set obstacles
    for (QJsonValueRef o : obstacles.get_stationary_obstacles()) {
        QJsonObject obstacle = o.toObject();
        double obs_lat = obstacle["latitude"].toDouble();
        double obs_lon = obstacle["longitude"].toDouble();
        double radius = obstacle["cylinder_radius"].toDouble();
        double delta = meters_to_deg(radius, obs_lat);
        delta *= SCALE_CONSTANT;
        obs_lat *= SCALE_CONSTANT;
        obs_lon *= SCALE_CONSTANT;
        // ignore the z-axis for now
        for (double x = obs_lat-delta; x < obs_lat+delta; ++x) {
            for (double y = obs_lon-delta; y < obs_lon+delta; ++y) {
                _stateSpace->obstacleGrid().obstacleAt(x, y);
            }
        }
    }


    std::vector<std::pair<double, double>> result;
    for (int i = 0; i < 1000; i++) {
        _biRRT->grow();
        if (_biRRT->startSolutionNode() != nullptr) {
            qInfo() << "we did it";
            auto _previousSolution = _biRRT->getPath();
            for (Eigen::Vector2d v : _biRRT->getPath()) {
                qInfo() << v.x() << " " << v.y();
                result.push_back(std::pair<double, double>(v.x(), v.y()));
            }
            RRT::SmoothPath<Eigen::Vector2d>(_previousSolution, *_stateSpace);

            break;
        }
    }
    return result;
}
PlanMission::PlanMission() {}
// too lazy to implement ordering for these objects
void PlanMission::add_goal_point(Point p) {
    goal_points.push_back(p);
}
void PlanMission::set_obstacles(Obstacles o) {
    obstacles_z = o;
}
void PlanMission::add_serach_area(QPolygon poly) {
    search_areas.push_back(poly);
}
QList<QVector3D>* PlanMission::get_path(Point start_point) {
    std::vector<Point> path;
    std::vector<Point> prelim_path;
    prelim_path.push_back(start_point);
    auto sort_func = [&](Point a, Point b) { return Point::euclidian_distance(prelim_path.back(), a) > Point::euclidian_distance(prelim_path.back(), b); };
    std::vector<Point> remaining_points(goal_points.begin(), goal_points.end());
    qInfo() << "start: " << start_point;
    // add search areas to remaining_points
    // generate rectangle
    // gen search path

    // generate prelim serach path
    std::vector<Point> pts = remaining_points;
    for (Point p : remaining_points) {
        // sort
        std::make_heap(pts.begin(), pts.end(),
                        sort_func);

        // pop
        std::pop_heap(pts.begin(), pts.end());
        Point next = pts.back();
        pts.pop_back();
        qInfo() << "prelim: " << next;
        prelim_path.push_back(p);
    }

    // pathfind around obstacles
    Point last_point = start_point;
    for (Point p : remaining_points) {
        qInfo() << last_point.toGeodetic() << " -> " << p.toGeodetic();
        // if segment defined by <last_point, p> intersects cylinder o {
        if (obstacles_z.segmentIntersectsObstacles(last_point, p)) {
            qInfo() << "we borked; starting RRT";
            // pathfind around obstacles
            auto detour = pathfind(last_point.toGeodetic()[0], last_point.toGeodetic()[1], p.toGeodetic()[0], p.toGeodetic()[1], obstacles_z);
            for (auto it = detour.begin()+1; it != detour.end(); ++it) {
                qInfo() << it->first/SCALE_CONSTANT << "/" << it->second/SCALE_CONSTANT;
                qInfo() << Point::fromGeodetic(it->first/SCALE_CONSTANT, it->second/SCALE_CONSTANT, 0);
                path.push_back(Point::fromGeodetic(it->first/SCALE_CONSTANT, it->second/SCALE_CONSTANT, 0));
            }
            if (path.size() > 0) {
                last_point = path.back();
            } else {
                last_point = p;
            }
        } else {
            last_point = p;
            path.push_back(p);
        }
    }

    // inefficient but lets just do like this for now
    QList<QVector3D>* qlist_qvector3d = new QList<QVector3D>();
    qInfo() << "da path";
    for (Point p : path) {
        qInfo() << p.toGeodetic();
        //qlist_qvector3d->append(p.QVectorGeodetic());
        qlist_qvector3d->append(QVector3D(p.toGeodetic().at(0), p.toGeodetic().at(1) * -1, 0));
    }
    qInfo() << "done with path";
    return qlist_qvector3d;
}
