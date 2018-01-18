//#ifndef PLANMISSION_HPP
//#define PLANMISSION_HPP

//#include <algorithm>
//#include <set>

//#include <QPolygon>

//#include "obstacles.h"
//#include "point.hpp"

//class PlanMission
//{

//    public:
//        PlanMission();
//        void add_goal_point(Point p) {
//            goal_points.insert(p);
//        }
//        void add_obstacle(Obstacles o) {
//            obstacles.insert(o);
//        }
//        void add_serach_area(QPolygon poly) {
//            search_areas.insert(poly);
//        }
//        std::vector<Point> get_path(Point start_point) {
//            auto sort_func = [&](Point p) { return start_point.GoalDistanceEstimate(p); };
//            std::vector<Point> path(goal_points.size());
//            std::vector<Point> remaining_points(goal_points.begin(), goal_points.end());

//            // add search areas to remaining_points

//            // generate prelim serach path
//            for (Point p : remaining_points) {
//                // sort
//                std::make_heap(remaining_points.begin(), remaining_points.end(),
//                                sort_func);
                
//                // pop
//                std::pop_heap(remaining_points.begin(), remaining_points.end());
//                Point next = remaining_points.back();

//                path.push_back(next);
//            }

//            // pathfind around obstacles
//            for (Point p : path) {
//                for (Obstacles o : obstacles) {
//                    if (p.intersects(o)) {
//                        // remove point
//                        // a* between previous and removed point
//                        break;
//                    }
//                }
//            }
//        }
//    private:
//        std::set<Point> goal_points;
//        std::set<Obstacles> obstacles;
//        std::set<QPolygon> search_areas;
//};

//#endif // PLANMISSION_HPP
