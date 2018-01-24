#ifndef POINT_HPP
#define POINT_HPP
#include <cstdio>
#include <qmath.h>
#include <QString>
#include <QVector3D>
#include <tuple>
class Point
{
    // WGS84 constants
    static constexpr double WGS84_a = 6378.137;
    static constexpr double WGS84_e = 8.1819190842622e-2;
private:
    Point(double x, double y, double z) : x{x}, y{y}, z{z} {}
public:
    Point();
    double x, y, z;
    static double euclidian_distance(Point a, Point b) {
        return qPow(a.x - b.x, 2) + qPow(a.y - b.y, 2) + qPow(a.z - b.z, 2);
    }
    friend bool operator<(const Point& l, const Point& r)
    {
        return std::tie(l.x, l.y, l.z)
             < std::tie(r.x, r.y, r.z); // keep the same order
    }
    operator QString() const {
        return QString::number(x) + '/' + QString::number(y) + '/' + QString::number(z);
    }
    static Point fromECEF(double x, double y, double z) {
        return Point{x,y,z};
    }
    static Point fromGeodetic(double lat, double lon, double alt) {
        // prime vertical radius of curvature
        double N = WGS84_a / sqrt(1 - pow(WGS84_e, 2) * pow(sin(lat), 2));

        double x = (N+alt) * cos(lat) * cos(lon);
        double y = (N+alt) * cos(lat) * sin(lon);
        double z = ((1-pow(WGS84_e,2)) * N + alt) * sin(lat);
        return Point{x, y, z};
    }
    QVector3D toGeodetic() {
        double asq = pow(WGS84_a, 2);
        double esq = pow(WGS84_e, 2);
        double b = sqrt(asq*(1-esq));
        double bsq = pow(b, 2);
        double ep = sqrt((asq-bsq)/bsq);
        double p = sqrt(x*x+y*y);
        double th = atan2(WGS84_a*z,b*p);
        double lon = atan2(y,x);
        double lat = atan2(pow(z+ep*ep*b*sin(th),3),(p-esq*WGS84_a*pow(cos(th),3)));
        double N = WGS84_a/(sqrt(1-esq*pow(sin(lat),2)));
        double alt= p/cos(lat)-N;
        return QVector3D(lat, lon, alt);
    }

};
#endif // POINT_HPP
