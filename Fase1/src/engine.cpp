//
// Created by Sandro Duarte on 09/03/2023.
//
#include <engine.h>

using std::cout;
using std::endl;

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
    float ratio = static_cast<float>(w) / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, -10.0f ,15.0f);

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
    gluLookAt(1.0f,1.0f,1.0f,
              0.0f,0.0f,0.0f,
              0.0f,1.0f,0.0f);
    // Draw

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

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500 , 500);
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
