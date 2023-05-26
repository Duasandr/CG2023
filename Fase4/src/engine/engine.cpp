//
// Created by Sandro Duarte on 09/03/2023.
//
#include "engine.h"
#include "World.h"

using std::cout;
using std::endl;
using cg_engine::World;

World *gWorld;
int tracking = 0;

#ifndef NDEBUG
GLint gMode = GL_LINE;
#else
GLint gMode = GL_FILL;
#endif

void DrawAxis() {
    bool lightsOn = gWorld->GetLightsSize();
    float red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    float green[] = {0.0f, 1.0f, 0.0f, 1.0f};
    float blue[] = {0.0f, 0.0f, 1.0f, 1.0f};


    glPushMatrix(); // Save the current transformation matrix

    glBegin(GL_LINES);

    // X-axis in red
    if(lightsOn){
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    } else{
        glColor3f(red[0], red[1], red[2]);
    }
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    // Y-axis in green
    if(lightsOn){
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
    } else{
        glColor3f(green[0], green[1], green[2]);
    }
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    // Z-axis in blue
    if(lightsOn){
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    } else{
        glColor3f(blue[0], blue[1], blue[2]);
    }
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glColor3f(1,1,1);

    glEnd();

    glPopMatrix(); // Restore the previous transformation matrix
}


/**
 * Changes the window size. Called every time a window is altered.
 * @param w New width
 * @param h New height
 */
void ChangeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
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
    gluPerspective(gWorld->Camera().GetProjection().GetX(), ratio, gWorld->Camera().GetProjection().GetY(),
                   gWorld->Camera().GetProjection().GetZ());

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
    gluLookAt(gWorld->Camera().GetPosition().GetX(), gWorld->Camera().GetPosition().GetY(),
              gWorld->Camera().GetPosition().GetZ(),
              gWorld->Camera().GetLookAt().GetX(), gWorld->Camera().GetLookAt().GetY(),
              gWorld->Camera().GetLookAt().GetZ(),
              gWorld->Camera().GetUp().GetX(), gWorld->Camera().GetUp().GetY(), gWorld->Camera().GetUp().GetZ());

    // Sets a different polygon mode on keyboard pressed
    glPolygonMode(GL_FRONT, gMode);

    // Draw
#ifndef NDEBUG
    DrawAxis();
#endif
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
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else { // Middle button

        }
    } else if (state == GLUT_UP) {
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
    if (argc < 2) {
        std::cerr << "Invalid argument number" << std::endl;
        return 1;
    }

    // init GLUT and the window
    gWorld = World::Create(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(gWorld->Window().getWidth(), gWorld->Window().getHeight());
    glutCreateWindow(gWorld->Window().getTitle().c_str());


#ifndef __APPLE__
    glewInit();
#endif
    if (gWorld->GetLightsSize() != 0) {

        glEnable(GL_LIGHTING);

        float dark[4] = {0.2, 0.2, 0.2, 1.0};
        float white[4] = {1.0, 1.0, 1.0, 1.0};

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, dark);


        for (auto const light: *gWorld->GetLights()) {
            int lightId = light->GetId();

            glEnable(lightId);

            glLightfv(lightId, GL_AMBIENT, dark);
            glLightfv(lightId, GL_DIFFUSE, white);
            glLightfv(lightId, GL_SPECULAR, white);
        }
    }


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

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
