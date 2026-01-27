#include "GUIManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>

// Static instance for callbacks
GUIManager *GUIManager::instance = nullptr;

GUIManager::GUIManager()
    : currentState(EQUATION_INPUT),
      equationInput(""),
      errorMessage(""),
      equationValid(false),
      runOptimization(true),
      startX(5.0), startY(5.0),
      learningRate(0.01),
      xMin(-10.0), xMax(10.0),
      yMin(-10.0), yMax(10.0),
      resolution(50),
      cursorPos(0),
      showCursor(true),
      cursorBlinkCounter(0),
      windowWidth(800),
      windowHeight(600),
      currentConfigField(OPTIMIZE_FIELD),
      configInput("")
{
    instance = this;
}

GUIManager::~GUIManager()
{
    instance = nullptr;
}

void GUIManager::initialize(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D Surface Equation Visualizer - GUI");

    // Set background color
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    // Register callbacks
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialCallback);
    glutTimerFunc(500, timerCallback, 0);
}

void GUIManager::run()
{
    glutMainLoop();
}

// Static callback wrappers
void GUIManager::displayCallback()
{
    if (instance)
        instance->display();
}

void GUIManager::reshapeCallback(int w, int h)
{
    if (instance)
    {
        instance->windowWidth = w;
        instance->windowHeight = h;
        glViewport(0, 0, w, h);
        glutPostRedisplay();
    }
}

void GUIManager::keyboardCallback(unsigned char key, int x, int y)
{
    if (instance)
    {
        if (instance->currentState == EQUATION_INPUT)
        {
            instance->handleEquationInput(key);
        }
        else if (instance->currentState == CONFIGURATION)
        {
            instance->handleConfigurationInput(key);
        }
        else if (instance->currentState == ERROR_DISPLAY)
        {
            if (key == 13) // Enter
            {
                instance->currentState = EQUATION_INPUT;
            }
            else if (key == 27) // ESC
            {
                exit(0);
            }
        }
        glutPostRedisplay();
    }
}

void GUIManager::specialCallback(int key, int x, int y)
{
    if (instance)
    {
        instance->handleSpecialKeys(key);
        glutPostRedisplay();
    }
}

void GUIManager::timerCallback(int value)
{
    if (instance)
    {
        instance->cursorBlinkCounter++;
        if (instance->cursorBlinkCounter % 2 == 0)
        {
            instance->showCursor = !instance->showCursor;
        }
        glutPostRedisplay();
        glutTimerFunc(500, timerCallback, 0);
    }
}

void GUIManager::display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (currentState)
    {
    case EQUATION_INPUT:
        displayEquationInput();
        break;
    case CONFIGURATION:
        displayConfiguration();
        break;
    case ERROR_DISPLAY:
        displayError();
        break;
    case VISUALIZING:
        // Handled by Visualizer
        break;
    }

    glutSwapBuffers();
}

void GUIManager::displayEquationInput()
{
    float centerY = windowHeight / 2.0f;

    // Title
    glColor3f(0.3f, 0.8f, 1.0f);
    drawCenteredText("3D SURFACE EQUATION VISUALIZER", windowHeight - 80, GLUT_BITMAP_HELVETICA_18);

    // Instructions
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCenteredText("Enter an equation with variables x and y", centerY + 100);
    drawCenteredText("Examples: x^2+y^2  |  sin(x)*cos(y)  |  exp(-(x^2+y^2))", centerY + 70);

    // Input box
    float boxWidth = 600;
    float boxHeight = 40;
    float boxX = (windowWidth - boxWidth) / 2.0f;
    float boxY = centerY;

    drawBox(boxX, boxY, boxWidth, boxHeight, 0.2f, 0.2f, 0.25f);

    // Equation text
    glColor3f(1.0f, 1.0f, 1.0f);
    std::string displayText = equationInput;
    if (showCursor && cursorPos >= 0 && cursorPos <= (int)equationInput.length())
    {
        displayText.insert(cursorPos, "|");
    }
    drawText(displayText, boxX + 10, boxY + 12);

    // Error message
    if (!errorMessage.empty())
    {
        glColor3f(1.0f, 0.3f, 0.3f);
        drawCenteredText("Error: " + errorMessage, centerY - 60);
    }

    // Controls
    glColor3f(0.5f, 0.5f, 0.5f);
    drawCenteredText("Press ENTER to continue  |  ESC to exit", 60);

    // Supported functions
    glColor3f(0.4f, 0.6f, 0.8f);
    drawText("Functions: sin, cos, tan, exp, log, sqrt, abs, pow(x,y), min, max", 20, 30, GLUT_BITMAP_8_BY_13);
    drawText("Operators: + - * / ^ ( )", 20, 15, GLUT_BITMAP_8_BY_13);
}

void GUIManager::displayConfiguration()
{
    float startY = windowHeight - 100;
    float lineHeight = 35;

    // Title
    glColor3f(0.3f, 0.8f, 1.0f);
    drawCenteredText("CONFIGURATION", windowHeight - 50, GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.6f, 0.6f, 0.6f);
    drawCenteredText("Equation: " + equationInput, windowHeight - 80, GLUT_BITMAP_8_BY_13);

    // Configuration fields
    std::vector<std::string> fieldNames = {
        "Run Optimization (y/n): ",
        "Start X: ",
        "Start Y: ",
        "Learning Rate: ",
        "X Min: ",
        "X Max: ",
        "Y Min: ",
        "Y Max: ",
        "Resolution: ",
        "[Press ENTER to START]"};

    std::vector<std::string> fieldValues = {
        runOptimization ? "y" : "n",
        std::to_string(startX),
        std::to_string(startY),
        std::to_string(learningRate),
        std::to_string(xMin),
        std::to_string(xMax),
        std::to_string(yMin),
        std::to_string(yMax),
        std::to_string(resolution),
        ""};

    for (int i = 0; i < (int)fieldNames.size(); i++)
    {
        float y = startY - i * lineHeight;

        // Highlight current field
        if (i == currentConfigField)
        {
            glColor3f(0.3f, 0.3f, 0.4f);
            drawBox(50, y - 5, windowWidth - 100, 25, 0.3f, 0.3f, 0.4f);
            glColor3f(1.0f, 1.0f, 0.3f);
        }
        else
        {
            glColor3f(0.7f, 0.7f, 0.7f);
        }

        std::string displayText = fieldNames[i];
        if (i < (int)fieldValues.size() - 1 && i != currentConfigField)
        {
            displayText += fieldValues[i];
        }
        else if (i == currentConfigField && i != DONE_FIELD)
        {
            displayText += configInput;
            if (showCursor)
                displayText += "|";
        }

        drawText(displayText, 60, y);
    }

    // Instructions
    glColor3f(0.5f, 0.5f, 0.5f);
    drawCenteredText("Use UP/DOWN arrows to navigate | Type to edit | ENTER to confirm | ESC to go back", 30);
}

void GUIManager::displayError()
{
    glColor3f(1.0f, 0.3f, 0.3f);
    drawCenteredText("ERROR", windowHeight - 100, GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCenteredText(errorMessage, windowHeight / 2);

    glColor3f(0.7f, 0.7f, 0.7f);
    drawCenteredText("Press ENTER to return to equation input", 100);
}

void GUIManager::handleEquationInput(unsigned char key)
{
    if (key == 13) // Enter
    {
        validateAndProceed();
    }
    else if (key == 27) // ESC
    {
        exit(0);
    }
    else if (key == 8 || key == 127) // Backspace
    {
        if (cursorPos > 0)
        {
            equationInput.erase(cursorPos - 1, 1);
            cursorPos--;
        }
    }
    else if (key >= 32 && key < 127) // Printable characters
    {
        equationInput.insert(cursorPos, 1, key);
        cursorPos++;
    }
}

void GUIManager::handleConfigurationInput(unsigned char key)
{
    if (key == 13) // Enter
    {
        // Process current field
        try
        {
            switch (currentConfigField)
            {
            case OPTIMIZE_FIELD:
                runOptimization = (configInput == "y" || configInput == "Y" || configInput == "yes");
                break;
            case START_X_FIELD:
                startX = std::stod(configInput);
                break;
            case START_Y_FIELD:
                startY = std::stod(configInput);
                break;
            case LEARNING_RATE_FIELD:
                learningRate = std::stod(configInput);
                if (learningRate <= 0 || learningRate > 1.0)
                {
                    errorMessage = "Learning rate must be between 0 and 1";
                    currentState = ERROR_DISPLAY;
                    return;
                }
                break;
            case X_MIN_FIELD:
                xMin = std::stod(configInput);
                break;
            case X_MAX_FIELD:
                xMax = std::stod(configInput);
                break;
            case Y_MIN_FIELD:
                yMin = std::stod(configInput);
                break;
            case Y_MAX_FIELD:
                yMax = std::stod(configInput);
                break;
            case RESOLUTION_FIELD:
                resolution = std::stoi(configInput);
                if (resolution < 10 || resolution > 200)
                {
                    errorMessage = "Resolution must be between 10 and 200";
                    currentState = ERROR_DISPLAY;
                    return;
                }
                break;
            case DONE_FIELD:
                startVisualization();
                return;
            }

            // Move to next field
            configInput = "";
            currentConfigField = (ConfigField)((int)currentConfigField + 1);
        }
        catch (const std::exception &e)
        {
            errorMessage = "Invalid input: " + std::string(e.what());
            currentState = ERROR_DISPLAY;
        }
    }
    else if (key == 27) // ESC
    {
        currentState = EQUATION_INPUT;
        currentConfigField = OPTIMIZE_FIELD;
        configInput = "";
    }
    else if (key == 8 || key == 127) // Backspace
    {
        if (!configInput.empty())
        {
            configInput.pop_back();
        }
    }
    else if (key >= 32 && key < 127) // Printable characters
    {
        configInput += key;
    }
}

void GUIManager::handleSpecialKeys(int key)
{
    if (currentState == EQUATION_INPUT)
    {
        if (key == GLUT_KEY_LEFT && cursorPos > 0)
        {
            cursorPos--;
        }
        else if (key == GLUT_KEY_RIGHT && cursorPos < (int)equationInput.length())
        {
            cursorPos++;
        }
        else if (key == GLUT_KEY_HOME)
        {
            cursorPos = 0;
        }
        else if (key == GLUT_KEY_END)
        {
            cursorPos = equationInput.length();
        }
    }
    else if (currentState == CONFIGURATION)
    {
        if (key == GLUT_KEY_UP && currentConfigField > OPTIMIZE_FIELD)
        {
            configInput = "";
            currentConfigField = (ConfigField)((int)currentConfigField - 1);
        }
        else if (key == GLUT_KEY_DOWN && currentConfigField < DONE_FIELD)
        {
            configInput = "";
            currentConfigField = (ConfigField)((int)currentConfigField + 1);
        }
    }
}

void GUIManager::validateAndProceed()
{
    if (equationInput.empty())
    {
        errorMessage = "Please enter an equation";
        return;
    }

    parser = std::make_unique<EquationParser>(equationInput);

    if (!parser->validate(errorMessage))
    {
        currentState = ERROR_DISPLAY;
        return;
    }

    // Check that equation uses x and y
    auto vars = parser->getVariables();
    bool hasX = false, hasY = false;
    for (const auto &var : vars)
    {
        if (var == "x")
            hasX = true;
        if (var == "y")
            hasY = true;
    }

    if (!hasX || !hasY)
    {
        errorMessage = "Equation must use both x and y variables";
        currentState = ERROR_DISPLAY;
        return;
    }

    equationValid = true;
    currentState = CONFIGURATION;
    configInput = "";
}

void GUIManager::startVisualization()
{
    std::cout << "\n=== Starting Visualization ===" << std::endl;
    std::cout << "Equation: " << equationInput << std::endl;
    std::cout << "Bounds: [" << xMin << ", " << xMax << "] x [" << yMin << ", " << yMax << "]" << std::endl;
    std::cout << "Resolution: " << resolution << std::endl;

    // Create custom surface from equation
    currentSurface = std::make_unique<CustomSurface>(
        [this](double x, double y) -> double
        {
            return this->parser->evaluate(x, y, 0);
        });

    // Run optimization if requested
    if (runOptimization)
    {
        std::cout << "\nRunning optimization..." << std::endl;
        std::cout << "Start point: (" << startX << ", " << startY << ")" << std::endl;
        std::cout << "Learning rate: " << learningRate << std::endl;

        GradientDescent optimizer(currentSurface.get(), learningRate, 1000, 1e-6);
        optResult = std::make_unique<OptimizationResult>(optimizer.optimize(startX, startY));

        std::cout << "\nOptimization complete!" << std::endl;
        std::cout << "Converged: " << (optResult->converged ? "Yes" : "No") << std::endl;
        std::cout << "Iterations: " << optResult->iterations << std::endl;
        std::cout << "Minimum at: (" << optResult->minimumPoint.getX()
                  << ", " << optResult->minimumPoint.getY()
                  << ", " << optResult->minimumPoint.getZ() << ")" << std::endl;
    }

    // Create visualizer
    visualizer = std::make_unique<Visualizer>(currentSurface.get(), xMin, xMax, yMin, yMax, resolution);

    if (optResult)
    {
        visualizer->setOptimizationResult(optResult.get());
    }

    // Close current window and prepare new window
    int oldWindow = glutGetWindow();

    // Create new window for 3D visualization
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Surface Optimizer Visualization");

    // Enable depth testing and lighting for 3D window
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Set up light
    GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat light_diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // Register visualizer callbacks (don't call visualizer->initialize which would call glutInit again)
    glutDisplayFunc(Visualizer::displayCallback);
    glutReshapeFunc(Visualizer::reshapeCallback);
    glutKeyboardFunc(Visualizer::keyboardCallback);

    // Destroy old GUI window
    glutDestroyWindow(oldWindow);

    // Trigger initial display
    glutPostRedisplay();
}

void GUIManager::drawText(const std::string &text, float x, float y, void *font)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(font, c);
    }
}

void GUIManager::drawCenteredText(const std::string &text, float y, void *font)
{
    int width = getTextWidth(text, font);
    float x = (windowWidth - width) / 2.0f;
    drawText(text, x, y, font);
}

void GUIManager::drawBox(float x, float y, float width, float height, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Border
    glColor3f(r + 0.2f, g + 0.2f, b + 0.2f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

int GUIManager::getTextWidth(const std::string &text, void *font)
{
    int width = 0;
    for (char c : text)
    {
        width += glutBitmapWidth(font, c);
    }
    return width;
}