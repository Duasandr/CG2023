//
// Created by Sandro Duarte on 09/03/2023.
//
#include "engine.h"
#include "world/World.h"

using std::cout;
using std::endl;
using cg_engine::World;

World *gWorld;
int tracking = 0;

GLint gMode = GL_LINE;

void DrawAxis() {
    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f,0.0f,0.0f);
    glVertex3f(100.0f,0.0f,0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f,-100.0f,0.0f);
    glVertex3f(0.0f,100.0f,0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f,0.0f,-100.0f);
    glVertex3f(0.0f,0.0f,100.0f);

    glEnd();
}

/**
 * Changes the window size. Called every time a window is altered.
 * @param w New width
 * @param h New height
 */
void ChangeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = static_cast<float>(w) / static_cast<float>(h);

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(gWorld->Camera().GetProjection().GetX() ,ratio, gWorld->Camera().GetProjection().GetY() ,gWorld->Camera().GetProjection().GetZ());

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

/**
 * Renders a scene. Sets the camera, applies transformations and draws models.
 */
void RenderScene() {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(gWorld->Camera().GetPosition().GetX(), gWorld->Camera().GetPosition().GetY(), gWorld->Camera().GetPosition().GetZ(),
              gWorld->Camera().GetLookAt().GetX(), gWorld->Camera().GetLookAt().GetY(), gWorld->Camera().GetLookAt().GetZ(),
              gWorld->Camera().GetUp().GetX(), gWorld->Camera().GetUp().GetY(), gWorld->Camera().GetUp().GetZ());

    // Sets a different polygon mode on keyboard pressed
    glPolygonMode(GL_FRONT, gMode);

    // Draw
    DrawAxis();
    gWorld->Draw();

    // End of frame
    glutSwapBuffers();
}

/**
 * Processes regular keyboard keys.
 * @param c Key pressed
 * @param xx Mouse x coordinate
 * @param yy Mouse y coordinate
 */
void ProcessKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here
#ifndef NDEBUG
    cout << " Key pressed: " << c << endl;
#endif
    switch (c) {
        case 'l':
            gMode = GL_LINE;
            glutPostRedisplay();
            break;
        case 'p':
            gMode = GL_POINT;
            glutPostRedisplay();
            break;
        case 'f':
            gMode = GL_FILL;
            glutPostRedisplay();
            break;
        case 'w':
            gWorld->Camera().Move(cg_engine::CameraMovement::FORWARD);
            glutPostRedisplay();
            break;
        case 'a':
            gWorld->Camera().Move(cg_engine::CameraMovement::LEFT);
            glutPostRedisplay();
            break;
        case 's':
            gWorld->Camera().Move(cg_engine::CameraMovement::BACKWARD);
            glutPostRedisplay();
            break;
        case 'd':
            gWorld->Camera().Move(cg_engine::CameraMovement::RIGHT);
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

/**
 * Processes special keys from keyboard. From F keys to arrow keys.
 * @param key
 * @param xx Mouse x position
 * @param yy Mouse y position
 */
void ProcessSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here
#ifndef NDEBUG
        cout << "Special key pressed: " << key << endl;
#endif
}

void ProcessMouseButtons(int button, int state, int xx, int yy) {
    if (state == GLUT_DOWN)  {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else { // Middle button

        }
    }
    else if (state == GLUT_UP) {
        tracking = 0;
    }
}

void ProcessMouseMotion(int xx, int yy) {
    if (!tracking)
        return;

    if (tracking == 1) {
        gWorld->Camera().Rotate(xx, yy);
    }

    glutPostRedisplay();
}

/**
 * Main entry of the program.
 * Reads a configuration file and initializes Glut.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    if(argc < 2) {
        std::cerr << "Invalid argument number" << std::endl;
        return 1;
    }

    // init GLUT and the window
    gWorld = World::Create(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(gWorld->Window().getWidth() , gWorld->Window().getHeight());
    glutCreateWindow("CG@DI-UM");


#ifndef __APPLE__
    glewInit();
#endif

    glEnableClientState(GL_VERTEX_ARRAY);

    gWorld->LoadGroups();

// Required callback registry
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutIdleFunc(RenderScene);

// Callback registration for keyboard processing
    glutKeyboardFunc(ProcessKeys);
    glutSpecialFunc(ProcessSpecialKeys);
    glutMotionFunc(ProcessMouseMotion);
    glutMouseFunc(ProcessMouseButtons);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
