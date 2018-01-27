#include "plan_mission.hpp"

std::vector<Point> PlanMission::pathfind(Point start, Point end, Obstacles obstacles) {
    qInfo() << "pathfind";
    qInfo() << start.toGeodetic();
    qInfo() << start.toGeodetic();
    std::unique_ptr<RRT> rrt{new RRT(start, end, obstacles)};
    double dist = rrt->distance(rrt->startPos, rrt->endPos) * 1.25;
    for(int i = 0; i < rrt->max_iter; i++) {
        Node *q = rrt->perturb(start.x, start.y, start.z, dist);
        if (q) {
            Node *qNearest = rrt->nearest(q->position);
            qInfo() << "trying: " << Point::fromECEF(q->position.getX(), q->position.getY(), q->position.getZ()).toGeodetic();
            qInfo() << "distance to nearest node: " << rrt->distance(q->position, qNearest->position);
            if (rrt->distance(q->position, qNearest->position) < 30) {
                Vect newConfig = rrt->newConfig(q, qNearest);
                Point a = Point::fromECEF(qNearest->position.getX(), qNearest->position.getY(), qNearest->position.getZ());
                Point b = Point::fromECEF(newConfig.getX(), newConfig.getY(), newConfig.getZ());
                if (!rrt->obstacles.segmentIntersectsObstacles(a, b)) {
                    Node *qNew = new Node;
                    qNew->position = newConfig;
                    rrt->add(qNearest, qNew);
                }
            }
        }
        if (rrt->reached()) {
            qInfo() << Point::fromECEF(q->position.getX(), q->position.getY(), q->position.getZ()).toGeodetic();
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
        Point p = Point::fromECEF(pos.getX(), pos.getY(), pos.getZ());
        result.push_back(p);
        qInfo() << "rrt backtrack:" << p.toGeodetic();
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
            std::vector<Point> detour = pathfind(last_point, p, obstacles_z);
            for (Point p : detour) {
                qInfo() << "detour: " << p.toGeodetic();
            }
            if (detour.size() > 1) {
                path.insert(path.end(), detour.begin(), detour.end());
            }
            last_point = detour.back();
        } else {
            last_point = p;
        }
        path.push_back(p);
        qInfo() << "p: " << p.toGeodetic();
    }

    // inefficient but lets just do like this for now
    QList<QVector3D> qlist_qvector3d;
    qInfo() << "da path";
    for (Point p : path) {
        qInfo() << p.toGeodetic();
        qlist_qvector3d.append(p.toGeodetic());
    }
    qInfo() << "done with path";
    return qlist_qvector3d;
}
