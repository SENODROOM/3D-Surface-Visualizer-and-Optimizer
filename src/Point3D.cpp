#include "Point3D.h"

Point3D::Point3D() : x(0), y(0), z(0) {}

Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

Point3D Point3D::operator+(const Point3D &other) const
{
    return Point3D(x + other.x, y + other.y, z + other.z);
}

Point3D Point3D::operator-(const Point3D &other) const
{
    return Point3D(x - other.x, y - other.y, z - other.z);
}

Point3D Point3D::operator*(double scalar) const
{
    return Point3D(x * scalar, y * scalar, z * scalar);
}

double Point3D::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Point3D Point3D::normalize() const
{
    double mag = magnitude();
    if (mag == 0)
        return Point3D(0, 0, 0);
    return Point3D(x / mag, y / mag, z / mag);
}

void Point3D::print() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}