/*
  Name:        quad.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update: 03/09/2014
  Release:     18/09/2004
  Description: Simple opengl program
*/

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

void display(void);

void init(void);

int shape = 0;



int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Quad Test");
    init();
    glutDisplayFunc(display);

    printf("Pressione ESC para fechar.\n");
    printf("Pressione A e D para mudar.\n");

    glutMainLoop();

    return 0;
}

void renderGrid() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -2, 0.0);
    glVertex3f(0.0, 2, 0.0);

    glVertex3f(-10.0, 0.0, 0.0);
    glVertex3f(390.0, 0.0, 0.0);
    glEnd();
}

void renderCurve(int sample, float R = 1, float G = 1, float B = 1) {
    const double round = M_PI * 2;

    glColor3f(R, G, B);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < sample + 1; ++i) {
        double x = 360 / sample * i;
        double y = sin((round / sample) * i);
        glVertex3f(x, y, 0.0);
    }
    glEnd();

}


void display(void) {
    // Limpar todos os pixels
    glClear(GL_COLOR_BUFFER_BIT);
    renderGrid();
    renderCurve(6, 1, 0, 0);
    renderCurve(12, 0, 1, 0);
    renderCurve(180, 1, 0, 1);

    glutSwapBuffers();
}


void init(void) {
    // selecionar cor de fundo (preto)
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
    glLoadIdentity();
    glOrtho(-10.0, 390, -2, 2, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
    glLoadIdentity();           // Inicializa com matriz identidade
}

