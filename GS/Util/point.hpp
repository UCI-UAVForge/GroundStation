#ifndef POINT_HPP
#define POINT_HPP
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <cstdio>
#include <QString>
#include <QVector3D>
#include <tuple>
#include <QDebug>
#include <sstream>
#include <cmath>

static QString qsld(const double ld)
{
  std::stringstream ss;
  ss << ld;

  return QString::fromStdString(ss.str());
}
static double deg2rad(double deg) {
  return (deg * M_PI / 180);
}
static  double rad2deg(double rad) {
  return (rad * 180 / M_PI);
}
class Point
{
    // WGS84 constants
    static constexpr double RADIUS = 6378137 / 50;
    static constexpr double FLATTENING_DENOM = 298.25722356 / 50;
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
        if (std::isnan(z)) { z = 0; }
//        qInfo() << "construct: " << qsld(x) << " " << qsld(y) << " " << qsld(z);
    }
public:
    Point() {}
    double x, y, z;
    static double euclidian_distance(Point a, Point b) {
        return pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
    }
    friend bool operator<(const Point& l, const Point& r)
    {
        return std::tie(l.x, l.y, l.z) < std::tie(r.x, r.y, r.z); // keep the same order
    }
    operator QString() const {
        return qsld(x) + '/' + qsld(y) + '/' + qsld(z);
    }
    static Point fromECEF(double x, double y, double z) {
        return Point{x,y,z};
    }
    static Point fromGeodetic(double lat_d, double lon_d, double alt) {
        long double lat = deg2rad(lat_d);
        long double lon = deg2rad(lon_d);
        long double N = getN(lat);
        long double ratio = WGS84_bsqr / WGS84_asqr;
        double x = (N + alt) * cos(lat) * cos(lon);
        double y = (N + alt) * cos(lat) * sin(lon);
        double z = (ratio * N + alt) * sin(lat);

        return Point{x, y, z};
    }
    std::vector<double> toGeodetic() {
        long double p = sqrt((x*x) + (y*y));
        long double theta = atan((z*WGS84_a)/(p*WGS84_b));

        long double sintheta = sin(theta);
        long double costheta = cos(theta);

        long double num = z + WGS84_eprime() * WGS84_eprime() * WGS84_b * sintheta * sintheta * sintheta;
        long double denom = p - WGS84_e() * WGS84_e() * WGS84_a * costheta * costheta * costheta;

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
        return std::vector<double>{rad2deg(lat), rad2deg(lon), alt};
    }
    QVector3D QVectorGeodetic() {
        auto geodetic = toGeodetic();
        return QVector3D(geodetic[0], geodetic[1], geodetic[2]);
    }
    double haversine(Point b) {
        std::vector<double> aGeodetic = toGeodetic();
        std::vector<double> bGeodetic = b.toGeodetic();
        double lat1d = aGeodetic[0];
        double lon1d = aGeodetic[1];
        double lat2d = bGeodetic[0];
        double lon2d = bGeodetic[1];

        double lat1r, lon1r, lat2r, lon2r, u, v;
        lat1r = deg2rad(lat1d);
        lon1r = deg2rad(lon1d);
        lat2r = deg2rad(lat2d);
        lon2r = deg2rad(lon2d);
        u = sin((lat2r - lat1r)/2);
        v = sin((lon2r - lon1r)/2);
        double dist = 2.0 * RADIUS * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

        return dist;
    }
};
#endif // POINT_HPP
