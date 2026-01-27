#include "GUIManager.h"
#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "=== 3D Surface Equation Visualizer ===" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "\nStarting GUI interface..." << std::endl;
    std::cout << "\nThis program allows you to:" << std::endl;
    std::cout << "  1. Enter any mathematical equation with variables x, y, z" << std::endl;
    std::cout << "  2. Configure visualization and optimization parameters" << std::endl;
    std::cout << "  3. View the 3D surface and optimization path" << std::endl;
    std::cout << "\nSupported operations:" << std::endl;
    std::cout << "  Basic: +, -, *, /, ^, ()" << std::endl;
    std::cout << "  Functions: sin, cos, tan, exp, log, sqrt, abs, pow(x,y)" << std::endl;
    std::cout << "\nGUI will open in a new window...\n"
              << std::endl;

    try
    {
        GUIManager gui;
        gui.initialize(argc, argv);
        gui.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}