#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "Surface.h"
#include "Optimizer.h"
#include <GL/glut.h>

class Visualizer
{
private:
    const Surface *surface;
    OptimizationResult *optResult;

    // View parameters
    float rotationX, rotationY;
    float zoom;

    // Mesh parameters
    double xMin, xMax, yMin, yMax;
    int resolution;

public:
    Visualizer(const Surface *surf, double xMin = -5, double xMax = 5,
               double yMin = -5, double yMax = 5, int res = 50);

    void setOptimizationResult(OptimizationResult *result);
    void initialize(int argc, char **argv);
    void run();

    // Static callbacks for GLUT
    static void displayCallback();
    static void reshapeCallback(int w, int h);
    static void keyboardCallback(unsigned char key, int x, int y);

private:
    void display();
    void drawSurface();
    void drawOptimizationPath();
    void drawAxes();

    static Visualizer *instance;
};

#endif