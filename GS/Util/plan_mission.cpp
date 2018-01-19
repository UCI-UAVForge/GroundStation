#include "plan_mission.hpp"

std::vector<Point> PlanMission::pathfind(Point start, Point end, std::vector<Obstacles> obstacles) {
    std::unique_ptr<RRT> rrt{new RRT(start, end, obstacles)};
    for(int i = 0; i < rrt->max_iter; i++) {
        Node *q = rrt->getRandomNode();
        if (q) {
            Node *qNearest = rrt->nearest(q->position);
            if (rrt->distance(q->position, qNearest->position) > rrt->step_size) {
                Vect newConfig = rrt->newConfig(q, qNearest);
//                if (!rrt->obstacles->isSegmentInObstacle(newConfig, qNearest->position)) {
//                    Node *qNew = new Node;
//                    qNew->position = newConfig;
//                    rrt->add(qNearest, qNew);
//                }
            }
        }
        if (rrt->reached()) {
            qDebug() << "Reached Destination!";
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
        qDebug() << "Exceeded max iterations! Path may intersect obstacle!";
    }
    // generate shortest path to destination.
    std::vector<Point> result;
    while (q != NULL) {
        rrt->path.push_back(q);
        Vect pos = q->position;
        result.push_back(Point(pos.getX(), pos.getY(), pos.getZ()));
        q = q->parent;
    }
    return result;
}
PlanMission::PlanMission() {}
// too lazy to implement ordering for these objects
void PlanMission::add_goal_point(Point p) {
    goal_points.push_back(p);
}
void PlanMission::add_obstacle(Obstacles o) {
    obstacles_z.push_back(o);
}
void PlanMission::add_serach_area(QPolygon poly) {
    search_areas.push_back(poly);
}
std::vector<Point> PlanMission::get_path(Point start_point) {
    auto sort_func = [&](Point a, Point b) { return Point::euclidian_distance(start_point, a) > Point::euclidian_distance(start_point, b); };
    std::vector<Point> path(goal_points.size());
    std::vector<Point> prelim_path(goal_points.size());
    std::vector<Point> remaining_points(goal_points.begin(), goal_points.end());

    // add search areas to remaining_points

    // generate prelim serach path
    for (Point p : remaining_points) {
        // sort
        std::make_heap(remaining_points.begin(), remaining_points.end(),
                        sort_func);

        // pop
        std::pop_heap(remaining_points.begin(), remaining_points.end());
        Point next = remaining_points.back();

        prelim_path.push_back(next);
    }

    // pathfind around obstacles
    Point last_point = path[0];
    for (Point p : prelim_path) {
        for (Obstacles o : obstacles_z) {
            // https://math.stackexchange.com/a/980131
            // if segment defined by <last_point, p> intersects cylinder o {
            if (false) {
                // pathfind around obstacles
                std::vector<Point> detour = pathfind(last_point, p, obstacles_z);
                path.insert(path.end(), detour.begin(), detour.end());
                break;
            }
        }
        last_point = p;
        path.push_back(p);
    }
    return path;
}
