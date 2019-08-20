/*
  Name:         triangle_anim.cpp
  Copyright:    Version 0.1
  Author:       Rodrigo Luis de Souza da Silva
  Last Update:  29/11/2018 (Animation based on FPS)
  Release:      28/10/2004
  Description:  Animação de triângulo usando função idle.
                Update: visualização e escolhe do FPS desejado
*/

#include <iostream>
#include <GL/glut.h>
//#include <glcFPSViewer.h>

using namespace std;

float desiredFPS = 60;
float var = 0.0f;
float dir = 1.0f;

const float step = 0.05;
float triangles[][3][4] = {
        {
                {5.0, 0.0, 0.05},
                {7.0, 5.0, 0.02},
                {1.0, 6.0, 0.09}
        },
        {
                {5.0, 3.0, 0.01},
                {8.0, 4.0, 0.04},
                {6.0, 8.0, 0.07}
        }
};
int directions[][3][3] = {
        {
                {1, 1},
                {1, 1},
                {1, 1},
        },
        {
                {1, 1},
                {1, 1},
                {1, 1},
        }
};


//glcFPSViewer *fpsViewer = new glcFPSViewer((char*) "Triangle Animation. ", (char*) " - Press ESC to Exit");

void display(void);

void init(void);

void idle();

void mouse(int button, int state, int x, int y);

void keyboard(unsigned char key, int x, int y);

bool isFullscreen = false;

void idle() {
    float t, desiredFrameTime, frameTime;
    static float tLast = 0.0;

    // Get elapsed time
    t = glutGet(GLUT_ELAPSED_TIME);
    // convert milliseconds to seconds
    t /= 1000.0;

    // Calculate frame time
    frameTime = t - tLast;
    // Calculate desired frame time
    desiredFrameTime = 1.0 / (float) (desiredFPS);

    // Check if the desired frame time was achieved. If not, skip animation.
    if (frameTime <= desiredFrameTime)
        return;


    if (var <= -0.001 || var >= 8.0)
        dir *= -1;
    var += dir * (step / desiredFPS); // Variation computed considering the FPS

    // Triangles
    for (int i = 0; i < 2; ++i) {
        // vertex
        for (int j = 0; j < 3; ++j) {
            // X / Y
            for (int k = 0; k < 2; ++k) {
                // fix direction
                if (triangles[i][j][k] < 0.0 || triangles[i][j][k] >= 8.0)
                    directions[i][j][k] *= -1;
                triangles[i][j][k] += triangles[i][j][2] * directions[i][j][k];
            }
        }
    }

    // Update tLast for next time, using static local variable
    tLast = t;

    glutPostRedisplay();

}

void display(void) {
    // Limpar todos os pixels
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(triangles[0][0][0], triangles[0][0][1]);
    glVertex2f(triangles[0][1][0], triangles[0][1][1]);
    glVertex2f(triangles[0][2][0], triangles[0][2][1]);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(triangles[1][0][0], triangles[1][0][1]);
    glVertex2f(triangles[1][1][0], triangles[1][1][1]);
    glVertex2f(triangles[1][2][0], triangles[1][2][1]);
    glEnd();

    glutSwapBuffers();

    // Print FPS
//    fpsViewer->drawFPS();
}

void init(void) {
    // selecionar cor de fundo (preto)
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 8.0, 0.0, 8.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void toggleFullscreen() {
    if (isFullscreen) {
        glutReshapeWindow(800, 600);
    } else {
        glutFullScreen();
    }
    isFullscreen = !isFullscreen;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
            toggleFullscreen();
//            desiredFPS = 10;
            break;
        case 27:
            exit(0);
            break;
    }
}




int main(int argc, char **argv) {
    glutInit(&argc, argv);
    cout << "Press F to go to FULLSCREEN" << endl;
    cout << "Press ESC to exit" << endl;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Screensaver");
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
