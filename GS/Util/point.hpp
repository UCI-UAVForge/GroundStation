#ifndef POINT_HPP
#define POINT_HPP
#include <cstdio>
#include <qmath.h>
#include <QString>
#include <QVector3D>
#include <tuple>
#include <QDebug>
#include <sstream>

static QString qsld(const double ld)
{
  std::stringstream ss;
  ss << ld;

  return QString::fromStdString(ss.str());
}

class Point
{
    // WGS84 constants
    static constexpr double RADIUS = 6378137;
    static constexpr double FLATTENING_DENOM = 298.257223563;
    static constexpr double FLATTENING = 1/FLATTENING_DENOM;
    static constexpr double POLAR_RADIUS = RADIUS * (1 - FLATTENING);
    static constexpr double WGS84_a = RADIUS;
    static constexpr double WGS84_f = FLATTENING;
    static constexpr double WGS84_b = POLAR_RADIUS;
    static constexpr double WGS84_asqr = WGS84_a * WGS84_a;
    static constexpr double WGS84_bsqr = WGS84_b * WGS84_b;
    static double WGS84_e() { return sqrt((WGS84_asqr-WGS84_bsqr)/WGS84_asqr); }
    static double WGS84_eprime() { return sqrt((WGS84_asqr-WGS84_bsqr)/WGS84_bsqr); }
    static double getN(double lat) {
        double sinlat = sin(lat);
        double denom = sqrt(1 - WGS84_e()*WGS84_e()*sinlat*sinlat);
        return WGS84_a / denom;
    }
private:
    Point(double x, double y, double z) : x{x}, y{y}, z{z} {
        qInfo() << "construct: " << qsld(x) << " " << qsld(y) << " " << qsld(z);
    }
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
        return qsld(x) + '/' + qsld(y) + '/' + qsld(z);
    }
    static Point fromECEF(double x, double y, double z) {
        return Point{x,y,z};
    }
    static Point fromGeodetic(double lat_d, double lon_d, double alt) {
        double lat = lat_d * M_PI/180.0;
        double lon = lon_d * M_PI/180.0;
        double N = getN(lat);
        double ratio = WGS84_bsqr / WGS84_asqr;
        double x = (N + alt) * cos(lat) * cos(lon);
        double y = (N + alt) * cos(lat) * sin(lon);
        double z = (ratio * N + alt) * sin(lat);

        return Point{x, y, z};
    }
    QVector3D toGeodetic() {
        double p = sqrt((x*x) + (y*y));
        double theta = atan((z*WGS84_a)/(p*WGS84_b));

        double sintheta = sin(theta);
        double costheta = cos(theta);

        double num = z + WGS84_eprime() * WGS84_eprime() * WGS84_b * sintheta * sintheta * sintheta;
        double denom = p - WGS84_e() * WGS84_e() * WGS84_a * costheta * costheta * costheta;

        double lat = atan(num/denom);
        double lon = atan(y/x);
        double N = getN(lat);
        double alt = (p / cos(lat) - N);

        if (x < 0 && y < 0) {
            lon = lon - M_PI;
        }

        if (x < 0 && y > 0) {
            lon = lon + M_PI;
        }
        qInfo() << qsld(lat * 180.0/M_PI) << " " << qsld(lon * 180.0/M_PI) << " " << qsld(alt);
        return QVector3D(lat * 180.0/M_PI, lon * 180.0/M_PI, alt);
    }

};
#endif // POINT_HPP
