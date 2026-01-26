#include "Visualizer.h"
#include <cmath>

// Static instance for GLUT callbacks
Visualizer *Visualizer::instance = nullptr;

Visualizer::Visualizer(const Surface *surf, double xMin, double xMax,
                       double yMin, double yMax, int res)
    : surface(surf), optResult(nullptr),
      rotationX(30.0f), rotationY(45.0f), zoom(30.0f),
      xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), resolution(res)
{
    instance = this;
}

void Visualizer::setOptimizationResult(OptimizationResult *result)
{
    optResult = result;
}

void Visualizer::initialize(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Surface Optimizer Visualization");

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Set up light
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = {0.7, 0.7, 0.7, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // Register callbacks
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
}

void Visualizer::run()
{
    glutMainLoop();
}

void Visualizer::displayCallback()
{
    if (instance)
        instance->display();
}

void Visualizer::reshapeCallback(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspect = (double)w / (double)h;
    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void Visualizer::keyboardCallback(unsigned char key, int x, int y)
{
    if (!instance)
        return;

    switch (key)
    {
    case 'w':
        instance->rotationX += 5.0f;
        break;
    case 's':
        instance->rotationX -= 5.0f;
        break;
    case 'a':
        instance->rotationY -= 5.0f;
        break;
    case 'd':
        instance->rotationY += 5.0f;
        break;
    case '+':
    case '=':
        instance->zoom -= 2.0f;
        if (instance->zoom < 5.0f)
            instance->zoom = 5.0f;
        break;
    case '-':
    case '_':
        instance->zoom += 2.0f;
        if (instance->zoom > 100.0f)
            instance->zoom = 100.0f;
        break;
    case 'r':
        instance->rotationX = 30.0f;
        instance->rotationY = 45.0f;
        instance->zoom = 30.0f;
        break;
    case 27: // ESC
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void Visualizer::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Position camera
    gluLookAt(0, 0, zoom, 0, 0, 0, 0, 1, 0);

    // Apply rotations
    glRotatef(rotationX, 1, 0, 0);
    glRotatef(rotationY, 0, 1, 0);

    drawAxes();
    drawSurface();

    if (optResult)
    {
        drawOptimizationPath();
    }

    glutSwapBuffers();
}

void Visualizer::drawAxes()
{
    glDisable(GL_LIGHTING);
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    // X axis - Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);

    // Y axis - Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);

    // Z axis - Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);

    glEnd();

    glEnable(GL_LIGHTING);
}

void Visualizer::drawSurface()
{
    double xStep = (xMax - xMin) / resolution;
    double yStep = (yMax - yMin) / resolution;

    glColor3f(0.5f, 0.7f, 1.0f); // Light blue surface

    for (int i = 0; i < resolution; ++i)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= resolution; ++j)
        {
            double x1 = xMin + i * xStep;
            double x2 = xMin + (i + 1) * xStep;
            double y = yMin + j * yStep;

            double z1 = surface->evaluate(x1, y);
            double z2 = surface->evaluate(x2, y);

            // Calculate normals for lighting
            Point3D grad1 = surface->gradient(x1, y);
            Point3D normal1(-grad1.getX(), -grad1.getY(), 1.0);
            normal1 = normal1.normalize();

            Point3D grad2 = surface->gradient(x2, y);
            Point3D normal2(-grad2.getX(), -grad2.getY(), 1.0);
            normal2 = normal2.normalize();

            glNormal3f(normal1.getX(), normal1.getY(), normal1.getZ());
            glVertex3f(x1, y, z1);

            glNormal3f(normal2.getX(), normal2.getY(), normal2.getZ());
            glVertex3f(x2, y, z2);
        }
        glEnd();
    }
}

void Visualizer::drawOptimizationPath()
{
    if (!optResult || optResult->path.empty())
        return;

    glDisable(GL_LIGHTING);

    // Draw path as thick red line
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);

    glBegin(GL_LINE_STRIP);
    for (const auto &point : optResult->path)
    {
        glVertex3f(point.getX(), point.getY(), point.getZ());
    }
    glEnd();

    // Draw start point as green sphere
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    Point3D start = optResult->path.front();
    glTranslatef(start.getX(), start.getY(), start.getZ());
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    // Draw end point (minimum) as large red sphere
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    Point3D end = optResult->path.back();
    glTranslatef(end.getX(), end.getY(), end.getZ());
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    glEnable(GL_LIGHTING);
}