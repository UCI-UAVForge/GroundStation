#include <map>
#include <cmath>
#include "obstacles.h"
#include <vector>
#include "kmedoid.h"
#include "point.hpp"
<<<<<<< HEAD:GS/Util/voronoi-mdp.cpp
const long NPOINTS = 1000000;
=======
constexpr long POINTS = 100;
>>>>>>> refs/remotes/origin/master:GS/Util/voronoi-mdp.hpp
static std::vector<Point> get_range(double resolution_distance) {
    std::vector<Point> v(NPOINTS);
    // generate space matrix points
    // let's just generate random points for now
    for (int i = 0; i < NPOINTS; ++i) {
        float alpha = randf(2 * M_PI);
        float beta = randf(2 * M_PI);
        float gamma = randf(2 * M_PI);
        float r = randf(resolution_distance);
        v.push_back(Point{r * cos(alpha), r * cos(beta), r * cos(gamma)});
    }
    return v;
}

static double global_occupancy_score(Point p, std::vector<Obstacles> obstacles) {
    int k = obstacles.size();
    if (k == 0) {
        return 0;
    }
    double score = 0;
    for (Obstacles o : obstacles) {
        if (p.intersects(o)) {
            return 1;
        }
        // score += 1/(euclidian distance from obstacle_i - radius of obstacle_i)
//        score += 1/(euclidian_distance(p, o) - o.radius);
    }
    return score/k;
}

static double local_occupancy_score(Point p, std::vector<Obstacles> obstacles) {
//    double score = 0;
//    double x,y,z;
//    x = p.x;
//    y = p.y;
//    z = p.z;
//    for (int i = x-1; i <= x+1; ++i) {
//        for (int j = y-1; j <= y+1; ++j) {
//            for (int k = z-1; k <= z+1; ++k) {
//                score += global_occupancy_score(Point{(double)i,(double)j,(double)k}, obstacles);
//            }
//        }
//    }
//    return score;
    return global_occupancy_score(p, obstacles);
}

static std::vector<Point> gen_path(std::vector<Point> goals, std::vector<Obstacles> obstacles) {
    // uav params
    float TURNING_RADIUS = 22; // in meters
    float DELTA = 0.7; // 70% chance of crashing???

    // start algorithm
    float resolution_distance = 2*TURNING_RADIUS;
    std::map<std::vector<double>, double> scores;

    // add goals
    for (Point p : get_range(resolution_distance)) {
        float score = 0;
        // if point in geofence
        score = 1;
        // else
        float global_score = global_occupancy_score(p, obstacles);
        float local_score = local_occupancy_score(p, obstacles);
        scores[std::vector<double>{p.x, p.y, p.z}] = fmax(global_score, local_score);
    }

    // filter points that are >= DELTA
    std::vector<std::vector<double>> sample_list;
    for (std::pair<std::vector<double>, double> pair : scores) {
        if (pair.second < DELTA) {
            sample_list.push_back(pair.first);
        }
    }


    // generate milestones with K-Medoids sampling
    int count = sample_list.size();
    point p, pt = (point)malloc(sizeof(point_t) * count);
    int i = 0;
    for (p = pt + count; p-- > pt; ++i) {
        p->x = sample_list[i][0];
        p->y = sample_list[i][1];
        p->z = sample_list[i][2];
    }
    point c = lloyd(pt, count, goals.size());
    std::map<Point, int> clusters;
    for (p = c + count; p-- > c;) {
        clusters[Point{p->x, p->y, p->z}] = p->group;
    }

    // sort milestones by distance from source point

    // generate A* through milestones
    std::vector<Point> path;
    for (int i = 1; i < goals.size(); ++i) {
        AStarSearch<Point> astarsearch;
        Point nodeStart = goals[i-1];
        Point nodeEnd = goals[i];
        nodeStart.setSuccessor(&nodeEnd);
        astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);

        unsigned int SearchState;

        do {
            SearchState = astarsearch.SearchStep();
        }
        while( SearchState == AStarSearch<Point>::SEARCH_STATE_SEARCHING );

        if( SearchState == AStarSearch<Point>::SEARCH_STATE_SUCCEEDED ) {
            qDebug() << "succeeded";
            Point* node = astarsearch.GetSolutionStart();
            int steps = 0;
            node->PrintNodeInfo();
            for( ;; )
            {
                node = astarsearch.GetSolutionNext();
                if( !node ) break;
                path.push_back(*node);
                qDebug() << node->x;
                node->PrintNodeInfo();
                steps ++;
            }
            // Once you're done with the solution you can free the nodes up
//            astarsearch.FreeSolutionNodes();
        }
        else if( SearchState == AStarSearch<Point>::SEARCH_STATE_FAILED ) {
            cout << "Search terminated. Did not find goal state\n";
        }
    }

    return path;
}
