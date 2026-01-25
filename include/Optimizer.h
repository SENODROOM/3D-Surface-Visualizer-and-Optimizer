#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Surface.h"
#include "Point3D.h"
#include <vector>

struct OptimizationResult
{
    Point3D minimumPoint;
    double minimumValue;
    int iterations;
    std::vector<Point3D> path; // Optimization path for visualization
    bool converged;
};

class Optimizer
{
protected:
    const Surface *surface;
    double learningRate;
    int maxIterations;
    double tolerance;

public:
    Optimizer(const Surface *surf, double lr = 0.1,
              int maxIter = 1000, double tol = 1e-6);
    virtual ~Optimizer() {}

    // Pure virtual optimization method
    virtual OptimizationResult optimize(double startX, double startY) = 0;
};

// Gradient Descent Optimizer
class GradientDescent : public Optimizer
{
public:
    GradientDescent(const Surface *surf, double lr = 0.1,
                    int maxIter = 1000, double tol = 1e-6);

    OptimizationResult optimize(double startX, double startY) override;
};

// Newton's Method Optimizer (uses Hessian)
class NewtonOptimizer : public Optimizer
{
public:
    NewtonOptimizer(const Surface *surf, double lr = 1.0,
                    int maxIter = 1000, double tol = 1e-6);

    OptimizationResult optimize(double startX, double startY) override;

private:
    // Calculate second partial derivatives for Hessian matrix
    double partialXX(double x, double y) const;
    double partialYY(double x, double y) const;
    double partialXY(double x, double y) const;
};

#endif