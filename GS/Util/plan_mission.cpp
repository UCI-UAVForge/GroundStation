#include "plan_mission.hpp"

std::vector<Point> PlanMission::pathfind(Point start, Point end, Obstacles obstacles) {
    std::unique_ptr<RRT> rrt{new RRT(start, end, obstacles)};
    for(int i = 0; i < rrt->max_iter; i++) {
        Node *q = rrt->getRandomNode();
        if (q) {
            Node *qNearest = rrt->nearest(q->position);
            if (rrt->distance(q->position, qNearest->position) > rrt->step_size) {
                Vect newConfig = rrt->newConfig(q, qNearest);
                Point a = Point::fromECEF(newConfig.getX(), newConfig.getY(), newConfig.getZ());
                Point b = Point::fromECEF(qNearest->position.getX(), qNearest->position.getY(), qNearest->position.getZ());
                if (!rrt->obstacles.segmentIntersectsObstacles(a, b)) {
                    Node *qNew = new Node;
                    qNew->position = newConfig;
                    rrt->add(qNearest, qNew);
                }
            }
        }
        if (rrt->reached()) {
            qInfo() << "RRT found a solution";
            break;
        }
    }
    Node *q;
    if (rrt->reached()) {
        q = rrt->lastNode;
    }
    else
    {
        // if not reached yet, then shortestPath will start from the closest node to end point.
        q = rrt->nearest(rrt->endPos);
        qInfo() << "Exceeded max iterations! Path may intersect obstacle!";
    }
    // generate shortest path to destination.
    std::vector<Point> result;
    while (q != NULL) {
        rrt->path.push_back(q);
        Vect pos = q->position;
        result.push_back(Point::fromECEF(pos.getX(), pos.getY(), pos.getZ()));
        q = q->parent;
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
QList<QVector3D> PlanMission::get_path(Point start_point) {
    auto sort_func = [&](Point a, Point b) { return Point::euclidian_distance(start_point, a) > Point::euclidian_distance(start_point, b); };
    std::vector<Point> path;
    std::vector<Point> prelim_path;
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
        prelim_path.push_back(next);
    }

    // pathfind around obstacles
    Point last_point = start_point;
    for (Point p : prelim_path) {
        // if segment defined by <last_point, p> intersects cylinder o {
        if (obstacles_z.segmentIntersectsObstacles(last_point, p)) {
            qInfo() << "we borked; starting RRT";
            // pathfind around obstacles
            std::vector<Point> detour = pathfind(last_point, p, obstacles_z);
            path.insert(path.end(), detour.begin(), detour.end());
            break;
        }
        last_point = p;
        path.push_back(p);
        qInfo() << "p: " << p;
    }

    // inefficient but lets just do like this for now
    QList<QVector3D> qlist_qvector3d;
    for (Point p : path) {
        qlist_qvector3d.append(p.toGeodetic());
    }
    qInfo() << "done with path";
    return qlist_qvector3d;
}
