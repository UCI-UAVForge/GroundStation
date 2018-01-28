#ifndef VECT_H
#define VECT_H

class Vect {
private:
    double x;
    double y;
    double z;

public:
    Vect() {
        x = 0;
        y = 0;
        z = 0;
    }
    Vect(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }

    double length() {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    Vect normalized() {
        double mag = length();

        return Vect(x / mag, y / mag, z / mag);
    }

    Vect neg() {
        return Vect(-x, -y, -z);
    }

    double dot(Vect other) {
        return x * other.getX() + y * other.getY() + z * other.getZ();
    }

    Vect cross(Vect other) {
        double x_ = y * other.getZ() - z * other.getY();
        double y_ = z * other.getX() - x * other.getZ();
        double z_ = x * other.getY() - y * other.getX();

        return Vect(x_, y_, z_);
    }

    Vect operator + (const Vect &other) {
        return Vect(x + other.x, y + other.y, z + other.z);
    }

    Vect operator - (const Vect &other) {
        return Vect(x - other.x, y - other.y, z - other.z);
    }

    Vect operator * (const Vect &other) {
        return Vect(x * other.x, y * other.y, z * other.z);
    }

    Vect operator * (const int &other) {
        return Vect(x * other, y * other, z * other);
    }

    Vect operator / (const Vect &other) {
        if (z == 0 || other.z == 0) {
            return Vect(x / other.x, y / other.y, 0);
        }
        return Vect(x / other.x, y / other.y, z / other.z);
    }
};
#endif // VECT_H
