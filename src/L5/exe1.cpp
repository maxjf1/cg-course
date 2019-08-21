#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

float rotationX = 25.0, rotationY = 0.0;
int last_x, last_y;
int width = 640, height = 480;

int distOrigem = 5;

float position[] = {0, 0};
float positionTransition[] = {0, 0};
const float speed = 0.1;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0);                   // habilita luz 0
    glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    glEnable(GL_LIGHTING);                 // Habilita luz
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    glEnable(GL_CULL_FACE);                // Habilita Backface-Culling
}

void renderGrid() {
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    glTranslatef(0, -0.5, 0);
    glRotatef(-90, 1, 0, 0);
    glPushMatrix();
    glBegin(GL_LINES);
    for (int i = 0; i < 6; ++i) {
        glVertex3f(-2.5, i - 2.5, 0);
        glVertex3f(2.5, i - 2.5, 0);
    }

    for (int i = 0; i < 6; ++i) {
        glVertex3f(i - 2.5, -2.5, 0);
        glVertex3f(i - 2.5, 2.5, 0);
    }
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) width / (GLfloat) height, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0);
    //glutSolidTorus(5.0f, 10.0f, 40, 40);
    glTranslatef(positionTransition[1], 0, positionTransition[0]);
    glutSolidCube(1.0f);
    glPopMatrix();

    renderGrid();

    glutSwapBuffers();
}

int getSignal(float val) {
    int signal = 1;
    if (val < 0)
        signal = -1;
    return signal;
}

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
    desiredFrameTime = 1.0 / (float) (60);

    // Check if the desired frame time was achieved. If not, skip animation.
    if (frameTime <= desiredFrameTime)
        return;

    for (int i = 0; i < 2; ++i) {
        if (position[i] == positionTransition[i]) continue;
        int direction = getSignal(position[i] - positionTransition[i]);
        positionTransition[i] += direction * speed;
        if (direction != getSignal(position[i] - positionTransition[i]))
            positionTransition[i] = position[i];

    }

    glutPostRedisplay();
}

void reshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'w':
            position[0]--;
            break;
        case 'a':
            position[1]--;
            break;
        case 's':
            position[0]++;
            break;
        case 'd':
            position[1]++;
            break;
        case '+' :
            distOrigem--;
            if (distOrigem < 20) distOrigem = 20;
            break;
        case '-' :
            distOrigem++;
            if (distOrigem > 180) distOrigem = 180;
            break;
        case 27:
            exit(0);
            break;
    }

    for (int i = 0; i < 2; ++i) {
        if (position[i] > 2)
            position[i] = 2;
        else if (position[i] < -2)
            position[i] = -2;
    }
}

// Motion callback
void motion(int x, int y) {
    rotationX += (float) (y - last_y);
    rotationY += (float) (x - last_x);

    last_x = x;
    last_y = y;
}

// Mouse callback
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        last_x = x;
        last_y = y;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(00, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
//    glutMotionFunc( motion );
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
