//
// Created by Sandro Duarte on 09/03/2023.
//
#include <engine.h>

using std::cout;
using std::endl;
using cg_engine::Scene;

Scene *gScene;

void DrawAxis() {
    glBegin(GL_LINES);
    glColor3f(.5, 0.5, 0.5);
    glVertex3f(-1,0,0);
    glVertex3f(1,0,0);

    glVertex3f(0,-1,0);
    glVertex3f(0,1,0);

    glVertex3f(0,0,-1);
    glVertex3f(0,0,1);

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
    gluPerspective(gScene->GetCamera().GetProjection().GetX() ,ratio, gScene->GetCamera().GetProjection().GetY() ,gScene->GetCamera().GetProjection().GetZ());

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
    gluLookAt(gScene->GetCamera().GetPosition().GetX(),gScene->GetCamera().GetPosition().GetY(),gScene->GetCamera().GetPosition().GetZ(),
              gScene->GetCamera().GetLookAt().GetX(),gScene->GetCamera().GetLookAt().GetY(),gScene->GetCamera().GetLookAt().GetZ(),
              gScene->GetCamera().GetUp().GetX(),gScene->GetCamera().GetUp().GetY(),gScene->GetCamera().GetUp().GetZ());
    // Draw
    DrawAxis();
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
    cout << "Key pressed: " << c << endl;
}

/**
 * Processes special keys from keyboard. From F keys to arrow keys.
 * @param key
 * @param xx Mouse x position
 * @param yy Mouse y position
 */
void ProcessSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here
        cout << "Special key pressed: " << key << endl;

}

/**
 * Main entry of the program.
 * Reads a configuration file and initializes Glut.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    gScene = Scene::Init("config.xml");
    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(gScene->GetWindowWidth() , gScene->GetWindowHeight());
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutIdleFunc(RenderScene);

    // Initializes Glew for Windows and Linux machines
#ifndef __APPLE__
    glewInit();
#endif

// Callback registration for keyboard processing
    glutKeyboardFunc(ProcessKeys);
    glutSpecialFunc(ProcessSpecialKeys);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
