/*
  Name:        circle2.cpp
  Author:      Rodrigo Luis de Souza da Silva
  Date:        07/05/2019
  Description: Círculo em um ambiente 3D
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

float rotationX = 0.0, rotationY = 0.0;
int last_x, last_y;
int width = 800, height = 800;

float distOrigem = 5.0f;

class vertex {
public:
    float x = 0, y = 0, z = 0;

    vertex(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

void glVertexv(vertex v) {
    glVertex3f(v.x, v.y, v.z);
}

class Shape {
public:
    vertex **grid;
    int width, height;

    Shape(int width, int height) : width(width), height(height) {
        for (int i = 0; i < width; ++i) {
            grid[i] = new vertex[height];
            for (int j = 0; j < height; ++j)
                grid[i][j] = vertex();
        }
    }

    void render() {
        for (int i = 0; i < width; ++i) {
            glBegin(GL_LINE_LOOP);
            for (int j = 0; j < height; ++j)
                glVertexv(grid[i][j]);
            glEnd();
        }

        for (int i = 0; i < height; ++i) {
            glBegin(GL_LINE_LOOP);
            for (int j = 0; j < width; ++j)
                glVertexv(grid[j][i]);
            glEnd();
        }
    }
};


// círculo terá 36 vértices
vertex v[36];

Shape criaCilindro(int sets = 5, int slices = 10, float height = 3, float radius = 1) {
    const float RAD = M_PI / 180;
    Shape c = Shape(sets, slices);
    float slice = 360.0 / c.height;

    for (int i = 0; i < c.width; ++i) {
        for (int j = 0; j < c.height; j++) {
            int g = j * slice;
            vertex v = vertex(
                    radius * cos(g * RAD),
                    radius * sin(g * RAD),
                    height / c.width * i
            );
            c.grid[i][j] = v;
        }
    }

    return c;
}


void criaCirculo() {
    float PI = 3.1415927;
    float raio = 1.5;
    int g, i;

    for (i = 0; i < 36; i++) {
        g = i * 10; // anda no círculo de 10 em 10 graus (para cobrir os 360 graus)
        v[i].x = raio * cos(g * PI / 180);
        v[i].y = raio * sin(g * PI / 180);
    }
}

void desenhaCirculo() {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 36; i++)
        glVertex3f(v[i].x, v[i].y, 0.0);
    glEnd();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0);                   // habilita luz 0
    glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    glEnable(GL_LIGHTING);                 // Habilita luz
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    glEnable(GL_CULL_FACE);                // Habilita Backface-Culling

    glLineWidth(4.0);

    criaCirculo();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) width / (GLfloat) height, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glColor3f(1.0f, 0.5f, 0.0);
    glPushMatrix();
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
//    glutSolidCube(1.0f);

    glDisable(GL_LIGHTING);
    criaCilindro(6, 41).render();

    glEnable(GL_LIGHTING);
    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void reshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 27:
            exit(0);
            break;
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
    if (button == 3) // Scroll up
    {
        if (distOrigem >= 3.0) distOrigem -= 0.25;

    }
    if (button == 4)   // Scroll down
    {
        if (distOrigem <= 20.0) distOrigem += 0.25;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}