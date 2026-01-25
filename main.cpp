#include <iostream>
#include <iomanip>
#include "Point3D.h"
#include "Surface.h"
#include "Optimizer.h"

void printOptimizationResult(const OptimizationResult &result)
{
    std::cout << "\n===== Optimization Results =====" << std::endl;
    std::cout << "Converged: " << (result.converged ? "Yes" : "No") << std::endl;
    std::cout << "Iterations: " << result.iterations << std::endl;
    std::cout << "Minimum point: ";
    result.minimumPoint.print();
    std::cout << "Minimum value: " << std::fixed << std::setprecision(6)
              << result.minimumValue << std::endl;

    std::cout << "\nOptimization path:" << std::endl;
    for (size_t i = 0; i < result.path.size(); i += result.path.size() / 10)
    {
        std::cout << "Step " << i << ": ";
        result.path[i].print();
    }
}

int main()
{
    // Create different surfaces
    std::cout << "=== Testing Paraboloid Surface ===" << std::endl;
    Paraboloid paraboloid;

    // Test gradient at a point
    double testX = 2.0, testY = 3.0;
    std::cout << "\nSurface value at (" << testX << ", " << testY << "): "
              << paraboloid.evaluate(testX, testY) << std::endl;

    Point3D grad = paraboloid.gradient(testX, testY);
    std::cout << "Gradient at this point: ";
    grad.print();

    // Optimize using Gradient Descent
    std::cout << "\n--- Gradient Descent ---" << std::endl;
    GradientDescent gd(&paraboloid, 0.1, 1000, 1e-6);
    OptimizationResult gdResult = gd.optimize(5.0, 5.0);
    printOptimizationResult(gdResult);

    // Optimize using Newton's Method
    std::cout << "\n--- Newton's Method ---" << std::endl;
    NewtonOptimizer newton(&paraboloid, 1.0, 100, 1e-6);
    OptimizationResult newtonResult = newton.optimize(5.0, 5.0);
    printOptimizationResult(newtonResult);

    // Test saddle surface
    std::cout << "\n\n=== Testing Saddle Surface ===" << std::endl;
    SaddleSurface saddle;
    GradientDescent gdSaddle(&saddle, 0.05, 1000, 1e-6);
    OptimizationResult saddleResult = gdSaddle.optimize(5.0, 5.0);
    printOptimizationResult(saddleResult);

    // Custom surface example: z = sin(x) * cos(y)
    std::cout << "\n\n=== Testing Custom Surface: z = sin(x)*cos(y) ===" << std::endl;
    CustomSurface custom([](double x, double y)
                         { return std::sin(x) * std::cos(y); });

    GradientDescent gdCustom(&custom, 0.1, 1000, 1e-6);
    OptimizationResult customResult = gdCustom.optimize(1.0, 1.0);
    printOptimizationResult(customResult);

    return 0;
}