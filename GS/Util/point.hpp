#ifndef POINT_HPP
#define POINT_HPP
#include "stlastar.h"
#include <cstdio>
template<typename T>
using triple = std::tuple<T, T, T>;


class Point
{
public:
    Point() {}
    Point(double x, double y, double z) : x{x}, y{y}, z{z} {}
    Point(std::vector<double> v) : x{v[0]}, y{v[1]}, z{v[2]} {}
    double x, y, z;
    bool intersects(Point p);
    bool intersects(Obstacles o);
    static double euclidian_distance(Point a, Point b) {
        return sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) + std::pow(a.z - b.z, 2));
    }
    void setSuccessor(Point* p) { successor = p; }

    // astar methods
    Point* successor = nullptr;
    float GoalDistanceEstimate( Point &nodeGoal );
    bool IsGoal( Point &nodeGoal );
    bool GetSuccessors( AStarSearch<Point> *astarsearch, Point *parent_node );
    float GetCost( Point &successor );
    bool IsSameState( Point &rhs );

    void PrintNodeInfo(FILE *stream) {
//        fprintf(stream, "x: %s, y: %s, z: %s\n", x, y, z);
    }
    void PrintNodeInfo() {
//        PrintNodeInfo(stdout);
    }
};

bool Point::intersects(Point p) {
    return this->x == p.x && this->y == p.y && this->z == p.z;
}
bool Point::intersects(Obstacles o) {
    return false;
}
bool operator< ( Point a, Point b ) { return triple<double>(a.x,a.y,a.z) < triple<double>(b.x,b.y,b.z); }

// To use the search class you must define the following calls...

// Data
//		Your own state space information
// Functions
//		(Optional) Constructor.
//		Nodes are created by the user, so whether you use a
//      constructor with parameters as below, or just set the object up after the
//      constructor, is up to you.
//
//		(Optional) Destructor.
//		The destructor will be called if you create one. You
//		can rely on the default constructor unless you dynamically allocate something in
//		your data
//
//		float GoalDistanceEstimate( PuzzleState &nodeGoal );
//		Return the estimated cost to goal from this node (pass reference to goal node)
//
//		bool IsGoal( PuzzleState &nodeGoal );
//		Return true if this node is the goal.
//
//		bool GetSuccessors( AStarSearch<PuzzleState> *astarsearch );
//		For each successor to this state call the AStarSearch's AddSuccessor call to
//		add each one to the current search - return false if you are out of memory and the search
//		will fail
//
//		float GetCost( PuzzleState *successor );
//		Return the cost moving from this state to the state of successor
//
//		bool IsSameState( PuzzleState &rhs );
//		Return true if the provided state is the same as this state
float Point::GoalDistanceEstimate( Point &nodeGoal ) {
    // TODO: better heuristic
    return euclidian_distance(*this, nodeGoal);
}
bool Point::IsGoal( Point &nodeGoal ) {
    return (x == nodeGoal.x) && (y == nodeGoal.y) && (z = nodeGoal.z);
}
bool Point::GetSuccessors( AStarSearch<Point> *astarsearch, Point *parent_node ) {
    if (successor) {
        astarsearch->AddSuccessor(*successor);
        return true;
    }
    return false;
}
float Point::GetCost( Point &successor ) {
    return GoalDistanceEstimate(successor);
}
bool Point::IsSameState( Point &rhs ) {
    return (x == rhs.x) && (y == rhs.y) && (z = rhs.z);
}

#endif // POINT_HPP
