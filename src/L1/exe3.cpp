/**
 * Exercice model
 *
 * Copy this file and add to CMakeLists
 */

#include <stdio.h>
#include <GL/glut.h>

const char TITLE[] = "MODEL";
const float ORTHO[] = {
        -1, 1,
        -1, 1
};

void display(void);

void init(void);

int shape = 0;

void renderGrid();

void renderShapes() {

    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);
    glVertex3d(0.1, 0.1, 0);
    glVertex3d(0.9, 0.1, 0);
    glVertex3d(0.1, 0.9, 0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0.5, 0.4);
    glVertex3d(0.1, -0.1, 0);
    glVertex3d(0.9, -0.1, 0);
    glVertex3d(0.1, -0.9, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex3d(-0.1, -0.1, 0);
    glVertex3d(-0.9, -0.1, 0);
    glVertex3d(-0.1, -0.9, 0);
    glVertex3d(-0.9, -0.9, 0);
    glEnd();
}

void display(void) {
    // Limpar todos os pixels
    glClear(GL_COLOR_BUFFER_BIT);

    /**
     * YOUR CODE HERE
     */

    // V1
    glViewport((int) 10, (int) 260, (int) 230, (int) 230);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    renderGrid();
    renderShapes();

    // V2
    glViewport((int) 260, (int) 260, (int) 230, (int) 230);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.1, 1, -0.1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    renderGrid();
    renderShapes();

    // V3
    glViewport((int) 260, (int) 10, (int) 230, (int) 230);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.1, 1, -1, 0.1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    renderGrid();
    renderShapes();

    // V3
    glViewport((int) 10, (int) 10, (int) 230, (int) 230);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 0.09, -1, 0.1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    renderGrid();
    renderShapes();


    glutSwapBuffers();
    glutPostRedisplay();

}

int main(int argc, char **argv) {
    printf("%s\n", TITLE);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(TITLE);
    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}


void init(void) {
    // BACKGROUND
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

/**
 * Render an grid
 */
void renderGrid() {
    glBegin(GL_LINES);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(ORTHO[0], (ORTHO[2] + ORTHO[3]) / 2, 0.0);
    glVertex3f(ORTHO[1], (ORTHO[2] + ORTHO[3]) / 2, 0.0);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f((ORTHO[0] + ORTHO[1]) / 2, ORTHO[2], 0.0);
    glVertex3f((ORTHO[0] + ORTHO[1]) / 2, ORTHO[3], 0.0);

    glEnd();
}