#ifndef SURFACE_H
#define SURFACE_H

#include "Point3D.h"
#include <functional>
#include <vector>

// Abstract base class for surfaces
class Surface
{
public:
    virtual ~Surface() {}

    // Pure virtual: Calculate z = f(x, y)
    virtual double evaluate(double x, double y) const = 0;

    // Calculate partial derivative with respect to x
    virtual double partialX(double x, double y) const;

    // Calculate partial derivative with respect to y
    virtual double partialY(double x, double y) const;

    // Calculate gradient vector at (x, y)
    Point3D gradient(double x, double y) const;

    // Generate mesh points for visualization
    std::vector<Point3D> generateMesh(double xMin, double xMax,
                                      double yMin, double yMax,
                                      int resolution) const;
};

// Concrete implementation: Paraboloid z = x^2 + y^2
class Paraboloid : public Surface
{
public:
    double evaluate(double x, double y) const override;
    double partialX(double x, double y) const override;
    double partialY(double x, double y) const override;
};

// Saddle surface z = x^2 - y^2
class SaddleSurface : public Surface
{
public:
    double evaluate(double x, double y) const override;
    double partialX(double x, double y) const override;
    double partialY(double x, double y) const override;
};

// Custom function surface (uses lambda/function)
class CustomSurface : public Surface
{
private:
    std::function<double(double, double)> func;

public:
    CustomSurface(std::function<double(double, double)> f) : func(f) {}
    double evaluate(double x, double y) const override;
};

#endif