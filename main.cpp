#include <iostream>
#include <iomanip>
#include "Point3D.h"
#include "Surface.h"
#include "Optimizer.h"
#include "Visualizer.h"

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

int main(int argc, char **argv)
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

    // Optimize using Gradient Descent
    std::cout << "\n--- Gradient Descent ---" << std::endl;
    GradientDescent gd(&paraboloid, 0.01, 1000, 1e-6);
    OptimizationResult gdResult = gd.optimize(5.0, 5.0);
    printOptimizationResult(gdResult);

    std::cout << "\n\n========================================" << std::endl;
    std::cout << "Opening 3D Visualization Window..." << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nControls:" << std::endl;
    std::cout << "  W/S - Rotate up/down" << std::endl;
    std::cout << "  A/D - Rotate left/right" << std::endl;
    std::cout << "  +/- - Zoom in/out" << std::endl;
    std::cout << "  R   - Reset view" << std::endl;
    std::cout << "  ESC - Exit" << std::endl;
    std::cout << "\nGreen sphere = Start point" << std::endl;
    std::cout << "Red sphere   = Minimum found" << std::endl;
    std::cout << "Red line     = Optimization path\n"
              << std::endl;

    // Create visualizer for paraboloid
    Visualizer viz(&paraboloid, -10, 10, -10, 10, 50);
    viz.setOptimizationResult(&gdResult);

    // Initialize and run visualization
    viz.initialize(argc, argv);
    viz.run();

    return 0;
}