#ifndef POINT_HPP
#define POINT_HPP
#include <cstdio>
#include "obstacles.h"
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
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
    }
    friend bool operator<(const Point& l, const Point& r)
    {
        return std::tie(l.x, l.y, l.z)
             < std::tie(r.x, r.y, r.z); // keep the same order
    }
};

#endif // POINT_HPP
