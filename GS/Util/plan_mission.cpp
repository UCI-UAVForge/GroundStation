#include "plan_mission.hpp"
#include <stack>
#include <memory>
#include "missionstatespace.h"
#include <rrt/2dplane/2dplane.hpp>
#include <rrt/BiRRT.hpp>
#include <rrt/planning/Path.hpp>
#include <Eigen/src/Core/Matrix.h>
double SCALE_CONSTANT = 1000;
std::vector<std::pair<double, double>> PlanMission::pathfind(double start_lat, double start_lon, double end_lat, double end_lon, QList<FlyZone> flyzones) {
    int dimensions = 2;

    Eigen::Vector2d size(90000,200000);
    std::vector<Eigen::Vector2d> _previousSolution;

    std::shared_ptr<MissionStateSpace> _stateSpace(new MissionStateSpace(size.x(), size.y(), 20, 20, FlyZone(flyzones.at(0))));
    std::shared_ptr<RRT::BiRRT<Eigen::Vector2d>> _biRRT = std::make_shared<RRT::BiRRT<Eigen::Vector2d>>(_stateSpace, RRT::hash, dimensions);

    auto _waypointCacheMaxSize = 15;

    Eigen::Vector2d _startPos = Eigen::Vector2d(start_lat*SCALE_CONSTANT, abs(start_lon)*SCALE_CONSTANT);
    Eigen::Vector2d _goalPos = Eigen::Vector2d(end_lat*SCALE_CONSTANT, abs(end_lon)*SCALE_CONSTANT);
    _stateSpace->endpoints[0] = _startPos;
    _stateSpace->endpoints[1] = _goalPos;

    qInfo() << _startPos.x() << " " << _startPos.y();
    qInfo() << _goalPos.x() << " " << _goalPos.y();
    //  setup birrt
    _biRRT->setStartState(_startPos);
    _biRRT->setGoalState(_goalPos);
    _biRRT->setMaxStepSize(PlanMission::meters_to_deg(50, _startPos.x()) * SCALE_CONSTANT);
    _biRRT->setGoalMaxDist(PlanMission::meters_to_deg(20, _goalPos.x()) * SCALE_CONSTANT);

    // set obstacles
    for (QPolygonF obst_poly : get_obstacles()) {
         _stateSpace->addObstacle(obst_poly);
    };

    std::vector<std::pair<double, double>> result;
    for (int i = 0; i < 200000; i++) {
        _biRRT->grow();
        if (_biRRT->startSolutionNode() != nullptr) {
            qInfo() << "we did it";
            auto _previousSolution = _biRRT->getPath();
            RRT::SmoothPath<Eigen::Vector2d>(_previousSolution, *_stateSpace);

            for (Eigen::Vector2d v : _previousSolution) {
                qInfo() << v.x() << " " << v.y();
                result.push_back(std::pair<double, double>(v.x(), v.y()));
            }
            break;
        }
    }
    return result;
}
// too lazy to implement ordering for these objects
void PlanMission::add_goal_point(Point p) {
    goal_points.push_back(p);
}
void PlanMission::set_obstacles(Obstacles o) {
    obstacles_z = o;
}
void PlanMission::add_serach_area(QPolygonF poly) {
    search_areas.push_back(poly);
}

QList<QVector3D> * PlanMission::get_path() {
    QList<FlyZone> flyzones = mission->fly_zones;
    for (int i = 1; i < mission->interopPath.waypoints.size(); i++) {
        QVector3D point = mission->interopPath.waypoints.at(i).coords;
        add_goal_point(Point::fromGeodetic(point.x(), point.y(), point.z()));
    }
    QVector3D start_point_q3d = mission->interopPath.waypoints.at(0).coords;
    Point start_point = Point::fromGeodetic(start_point_q3d.x(), start_point_q3d.y(), start_point_q3d.z());
    set_obstacles(mission->obstacles);
    std::vector<Point> path;
//    path.push_back(start_point);
    std::vector<Point> prelim_path;
//    prelim_path.push_back(start_point);
    auto sort_func = [&](Point a, Point b) { return Point::euclidian_distance(prelim_path.back(), a) > Point::euclidian_distance(prelim_path.back(), b); };
    std::vector<Point> remaining_points(goal_points.begin(), goal_points.end());
    qInfo() << "start: " << start_point;
    // add search areas to remaining_points
    // generate rectangle
    QList<QVector3D>* waypoints = mission->search_grid_points;
    QVector<QPointF> list;
    for (int i = 0; i < waypoints->length(); i++) {
        list.append(waypoints->at(i).toPointF());
    }
    QRectF bounding_rect = QPolygonF().boundingRect();
    // gen search path
    QPointF tl = bounding_rect.topLeft();
    QPointF br = bounding_rect.bottomRight();
    float delta = meters_to_deg(80, start_point_q3d.x());
    for (float i = tl.x(); i < br.x(); i+delta) {
        for (float j = tl.y(); j < br.y(); j+delta) {
            remaining_points.push_back(Point::fromGeodetic(i, j, start_point_q3d.z()));
        }
    }

    // generate prelim serach path
    std::vector<Point> pts = remaining_points;
    for (Point p : remaining_points) {
        // sort
//        std::make_heap(pts.begin(), pts.end(),
//                        sort_func);

        // pop
        std::pop_heap(pts.begin(), pts.end());
        Point next = pts.back();
        pts.pop_back();
        qInfo() << "prelim: " << next;
        prelim_path.push_back(p);
    }

    // pathfind around obstacles
    Point last_point = start_point;
    QList<QPolygonF> obstacle_polys = get_obstacles();

    for (Point p : remaining_points) {
        qInfo() << last_point.toGeodetic() << " -> " << p.toGeodetic();
        // if segment defined by <last_point, p> intersects cylinder o {
        bool intersects = false;
        QPolygonF segment;
        segment.append(QPointF(last_point.toGeodetic()[0], last_point.toGeodetic()[1]));
        segment.append(QPointF(p.toGeodetic()[0], p.toGeodetic()[1]));
        for (QPolygonF obst_poly : obstacle_polys) {
            if (PlanMission::poly_intersects(obst_poly, segment)) {
                intersects = true;
                break;
            }
        }
        if (intersects) {
//        if (obstacles_z.segmentIntersectsObstacles(last_point, p)) {
            qInfo() << "we borked; starting RRT";
            // pathfind around obstacles
            auto detour = pathfind(last_point.toGeodetic()[0], last_point.toGeodetic()[1], p.toGeodetic()[0], p.toGeodetic()[1], flyzones);
            if (detour.size() > 1) {
                for (auto it = detour.begin()+1; it != detour.end(); ++it) {
                    qInfo() << it->first/SCALE_CONSTANT << "/" << it->second/SCALE_CONSTANT;
                    qInfo() << Point::fromGeodetic(it->first/SCALE_CONSTANT, it->second/SCALE_CONSTANT, p.toGeodetic()[2]);
                    path.push_back(Point::fromGeodetic(it->first/SCALE_CONSTANT, it->second/SCALE_CONSTANT, p.toGeodetic()[2]));
                }
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
    int sign = start_point.toGeodetic().at(1) < 0 ? -1 : 1;
    for (Point p : path) {
        qInfo() << p.toGeodetic();
        //qlist_qvector3d->append(p.QVectorGeodetic());
        qlist_qvector3d->append(QVector3D(p.toGeodetic().at(0),
                                          abs(p.toGeodetic().at(1)) * sign, p.toGeodetic().at(2)));
    }
    qInfo() << "done with path";
    return qlist_qvector3d;
}
