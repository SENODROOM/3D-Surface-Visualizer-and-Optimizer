#include "Optimizer.h"
#include <cmath>
#include <iostream>

Optimizer::Optimizer(const Surface *surf, double lr, int maxIter, double tol)
    : surface(surf), learningRate(lr), maxIterations(maxIter), tolerance(tol) {}

// Gradient Descent Implementation
GradientDescent::GradientDescent(const Surface *surf, double lr,
                                 int maxIter, double tol)
    : Optimizer(surf, lr, maxIter, tol) {}

OptimizationResult GradientDescent::optimize(double startX, double startY)
{
    OptimizationResult result;
    result.converged = false;

    double x = startX, y = startY;

    for (int iter = 0; iter < maxIterations; ++iter)
    {
        // Store current position
        double z = surface->evaluate(x, y);
        result.path.push_back(Point3D(x, y, z));

        // Calculate gradient: ∇f = (∂f/∂x, ∂f/∂y)
        Point3D grad = surface->gradient(x, y);

        // Check for convergence (gradient magnitude)
        double gradMag = std::sqrt(grad.getX() * grad.getX() +
                                   grad.getY() * grad.getY());

        if (gradMag < tolerance)
        {
            result.converged = true;
            result.iterations = iter;
            break;
        }

        // Update: x_new = x_old - learning_rate * ∂f/∂x
        x = x - learningRate * grad.getX();
        y = y - learningRate * grad.getY();

        result.iterations = iter + 1;
    }

    result.minimumPoint = Point3D(x, y, surface->evaluate(x, y));
    result.minimumValue = surface->evaluate(x, y);

    return result;
}

// Newton's Method Implementation
NewtonOptimizer::NewtonOptimizer(const Surface *surf, double lr,
                                 int maxIter, double tol)
    : Optimizer(surf, lr, maxIter, tol) {}

double NewtonOptimizer::partialXX(double x, double y) const
{
    const double h = 0.0001;
    return (surface->partialX(x + h, y) - surface->partialX(x - h, y)) / (2 * h);
}

double NewtonOptimizer::partialYY(double x, double y) const
{
    const double h = 0.0001;
    return (surface->partialY(x, y + h) - surface->partialY(x, y - h)) / (2 * h);
}

double NewtonOptimizer::partialXY(double x, double y) const
{
    const double h = 0.0001;
    return (surface->partialX(x, y + h) - surface->partialX(x, y - h)) / (2 * h);
}

OptimizationResult NewtonOptimizer::optimize(double startX, double startY)
{
    OptimizationResult result;
    result.converged = false;

    double x = startX, y = startY;

    for (int iter = 0; iter < maxIterations; ++iter)
    {
        double z = surface->evaluate(x, y);
        result.path.push_back(Point3D(x, y, z));

        // Hessian matrix: H = [[fxx, fxy], [fxy, fyy]]
        double fxx = partialXX(x, y);
        double fyy = partialYY(x, y);
        double fxy = partialXY(x, y);

        // Determinant of Hessian
        double det = fxx * fyy - fxy * fxy;

        if (std::abs(det) < 1e-10)
        {
            std::cout << "Singular Hessian encountered" << std::endl;
            break;
        }

        // Inverse Hessian
        double invH11 = fyy / det;
        double invH12 = -fxy / det;
        double invH22 = fxx / det;

        // Gradient
        Point3D grad = surface->gradient(x, y);
        double gx = grad.getX();
        double gy = grad.getY();

        // Check convergence
        if (std::sqrt(gx * gx + gy * gy) < tolerance)
        {
            result.converged = true;
            result.iterations = iter;
            break;
        }

        // Newton update: x_new = x_old - H^(-1) * ∇f
        double dx = invH11 * gx + invH12 * gy;
        double dy = invH12 * gx + invH22 * gy;

        x = x - learningRate * dx;
        y = y - learningRate * dy;

        result.iterations = iter + 1;
    }

    result.minimumPoint = Point3D(x, y, surface->evaluate(x, y));
    result.minimumValue = surface->evaluate(x, y);

    return result;
}