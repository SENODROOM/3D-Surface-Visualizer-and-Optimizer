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

    std::cout << "\nOptimization path (showing every 10th step):" << std::endl;
    int stepSize = std::max(1, (int)result.path.size() / 10);
    for (size_t i = 0; i < result.path.size(); i += stepSize)
    {
        std::cout << "Step " << std::setw(4) << i << ": ";
        result.path[i].print();
    }
}

int main()
{
    std::cout << "=== 3D Surface Visualizer and Optimizer ===" << std::endl;
    std::cout << "=========================================\n"
              << std::endl;

    // Create Paraboloid surface: z = x^2 + y^2
    std::cout << "Testing Paraboloid Surface: z = x^2 + y^2" << std::endl;
    Paraboloid paraboloid;

    // Test gradient at a point
    double testX = 2.0, testY = 3.0;
    std::cout << "\nSurface value at (" << testX << ", " << testY << "): "
              << paraboloid.evaluate(testX, testY) << std::endl;

    Point3D grad = paraboloid.gradient(testX, testY);
    std::cout << "Gradient at this point: ";
    grad.print();

    // Optimize using Gradient Descent with SMALLER learning rate
    std::cout << "\n--- Gradient Descent ---" << std::endl;
    GradientDescent gd(&paraboloid, 0.01, 1000, 1e-6); // Changed from 0.1 to 0.01
    OptimizationResult gdResult = gd.optimize(5.0, 5.0);
    printOptimizationResult(gdResult);

    // Optimize using Newton's Method
    std::cout << "\n--- Newton's Method ---" << std::endl;
    NewtonOptimizer newton(&paraboloid, 0.5, 100, 1e-6); // Changed from 1.0 to 0.5
    OptimizationResult newtonResult = newton.optimize(5.0, 5.0);
    printOptimizationResult(newtonResult);

    // Test saddle surface: z = x^2 - y^2
    std::cout << "\n\n=== Testing Saddle Surface: z = x^2 - y^2 ===" << std::endl;
    SaddleSurface saddle;
    GradientDescent gdSaddle(&saddle, 0.01, 1000, 1e-6); // Changed from 0.05 to 0.01
    OptimizationResult saddleResult = gdSaddle.optimize(5.0, 5.0);
    printOptimizationResult(saddleResult);

    // Custom surface example: z = sin(x) * cos(y)
    std::cout << "\n\n=== Testing Custom Surface: z = sin(x)*cos(y) ===" << std::endl;
    CustomSurface custom([](double x, double y)
                         { return std::sin(x) * std::cos(y); });

    GradientDescent gdCustom(&custom, 0.05, 2000, 1e-6); // Increased iterations
    OptimizationResult customResult = gdCustom.optimize(1.0, 1.0);
    printOptimizationResult(customResult);

    // Additional interesting surface: Rosenbrock function
    std::cout << "\n\n=== Testing Rosenbrock Function: z = (1-x)^2 + 100(y-x^2)^2 ===" << std::endl;
    CustomSurface rosenbrock([](double x, double y)
                             { return (1.0 - x) * (1.0 - x) + 100.0 * (y - x * x) * (y - x * x); });

    GradientDescent gdRosen(&rosenbrock, 0.0001, 5000, 1e-6);
    OptimizationResult rosenResult = gdRosen.optimize(0.0, 0.0);
    printOptimizationResult(rosenResult);

    std::cout << "\n\n=== Program Complete ===" << std::endl;

    return 0;
}