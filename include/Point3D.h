#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include <cmath>

class Point3D
{
private:
    double x, y, z;

public:
    // Constructors
    Point3D();
    Point3D(double x, double y, double z);

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Setters
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setZ(double z) { this->z = z; }

    // Vector operations
    Point3D operator+(const Point3D &other) const;
    Point3D operator-(const Point3D &other) const;
    Point3D operator*(double scalar) const;
    double magnitude() const;
    Point3D normalize() const;

    // Display
    void print() const;
};

#endif