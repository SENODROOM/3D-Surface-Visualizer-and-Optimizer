#include "Surface.h"

const double h = 0.0001; // Small value for numerical derivatives

double Surface::partialX(double x, double y) const
{
    // Numerical approximation: f'(x) ≈ [f(x+h) - f(x-h)] / 2h
    return (evaluate(x + h, y) - evaluate(x - h, y)) / (2 * h);
}

double Surface::partialY(double x, double y) const
{
    return (evaluate(x, y + h) - evaluate(x, y - h)) / (2 * h);
}

Point3D Surface::gradient(double x, double y) const
{
    // Gradient = (∂f/∂x, ∂f/∂y, 0)
    return Point3D(partialX(x, y), partialY(x, y), 0);
}

std::vector<Point3D> Surface::generateMesh(double xMin, double xMax,
                                           double yMin, double yMax,
                                           int resolution) const
{
    std::vector<Point3D> mesh;
    double xStep = (xMax - xMin) / resolution;
    double yStep = (yMax - yMin) / resolution;

    for (int i = 0; i <= resolution; ++i)
    {
        for (int j = 0; j <= resolution; ++j)
        {
            double x = xMin + i * xStep;
            double y = yMin + j * yStep;
            double z = evaluate(x, y);
            mesh.push_back(Point3D(x, y, z));
        }
    }

    return mesh;
}

// Paraboloid implementation
double Paraboloid::evaluate(double x, double y) const
{
    return x * x + y * y;
}

double Paraboloid::partialX(double x, double y) const
{
    return 2 * x; // Analytical derivative
}

double Paraboloid::partialY(double x, double y) const
{
    return 2 * y;
}

// Saddle surface implementation
double SaddleSurface::evaluate(double x, double y) const
{
    return x * x - y * y;
}

double SaddleSurface::partialX(double x, double y) const
{
    return 2 * x;
}

double SaddleSurface::partialY(double x, double y) const
{
    return -2 * y;
}

// Custom surface implementation
double CustomSurface::evaluate(double x, double y) const
{
    return func(x, y);
}