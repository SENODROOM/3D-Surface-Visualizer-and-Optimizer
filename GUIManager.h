#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "Surface.h"
#include "EquationParser.h"
#include "Optimizer.h"
#include "Visualizer.h"
#include <GL/glut.h>
#include <string>
#include <memory>

class GUIManager
{
public:
    enum GUIState
    {
        EQUATION_INPUT,
        CONFIGURATION,
        VISUALIZING,
        ERROR_DISPLAY
    };

private:
    GUIState currentState;

    // Equation input
    std::string equationInput;
    std::string errorMessage;
    bool equationValid;

    // Configuration
    bool runOptimization;
    double startX, startY;
    double learningRate;
    double xMin, xMax, yMin, yMax;
    int resolution;

    // Current surface and results
    std::unique_ptr<CustomSurface> currentSurface;
    std::unique_ptr<EquationParser> parser;
    std::unique_ptr<OptimizationResult> optResult;
    std::unique_ptr<Visualizer> visualizer;

    // Input cursor position
    int cursorPos;
    bool showCursor;
    int cursorBlinkCounter;

    // Window dimensions
    int windowWidth;
    int windowHeight;

    // Configuration input state
    enum ConfigField
    {
        OPTIMIZE_FIELD,
        START_X_FIELD,
        START_Y_FIELD,
        LEARNING_RATE_FIELD,
        X_MIN_FIELD,
        X_MAX_FIELD,
        Y_MIN_FIELD,
        Y_MAX_FIELD,
        RESOLUTION_FIELD,
        DONE_FIELD
    };

    ConfigField currentConfigField;
    std::string configInput;

    static GUIManager *instance;

public:
    GUIManager();
    ~GUIManager();

    void initialize(int argc, char **argv);
    void run();

    // Callbacks
    static void displayCallback();
    static void reshapeCallback(int w, int h);
    static void keyboardCallback(unsigned char key, int x, int y);
    static void specialCallback(int key, int x, int y);
    static void timerCallback(int value);

private:
    void display();
    void displayEquationInput();
    void displayConfiguration();
    void displayError();

    void handleEquationInput(unsigned char key);
    void handleConfigurationInput(unsigned char key);
    void handleSpecialKeys(int key);

    void validateAndProceed();
    void startVisualization();

    // Helper functions for rendering text
    void drawText(const std::string &text, float x, float y, void *font = GLUT_BITMAP_9_BY_15);
    void drawCenteredText(const std::string &text, float y, void *font = GLUT_BITMAP_9_BY_15);
    void drawBox(float x, float y, float width, float height,
                 float r = 1.0f, float g = 1.0f, float b = 1.0f);
    int getTextWidth(const std::string &text, void *font = GLUT_BITMAP_9_BY_15);
};

#endif