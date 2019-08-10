/*
  Name:        quad.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update: 03/09/2014
  Release:     18/09/2004
  Description: Simple opengl program
*/

#include <stdio.h>
#include <GL/glut.h>

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);
int shape = 0;


// Keyboard callback
void keyboardPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a' :
            shape++;
            break;

        case 'd' :
            shape--;
            break;
    }
    if(shape < 0)
        shape = 3;
    if(shape > 3)
        shape = 0;
    printf("foi");
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Quad Test");
    init ();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardFunc( keyboardPress );


    printf("Pressione ESC para fechar.\n");
    printf("Pressione A e D para mudar.\n");

    glutMainLoop();

    return 0;
}

void renderGrid(){
    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f (0.0, 1.2, 0.0);
    glVertex3f (0.0, -1.2, 0.0);

    glVertex3f (-1.2, 0.0, 0.0);
    glVertex3f (1.2, 0.0, 0.0);
    glEnd();
}

void renderTriangle(){
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (0.5, 1.0, 0.0);
    glVertex3f (1.0, 0.0, 0.0);
    glEnd();
}

void renderTriangleReverse(){
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (-0.5, -1.0, 0.0);
    glVertex3f (-1.0, 0.0, 0.0);
    glEnd();
}

void renderTranslucidTriangle(){
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f (0.0, 0, 0.0);
    glVertex3f (0.5, 1.0, 0.0);
    glVertex3f (1.0, 0, 0.0);
    glEnd();
}

void renderForm(){
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    glVertex3f (-0.5, 1.0, 0.0);
    glVertex3f (-1.0, 0, 0.0);
    glVertex3f (-0.5, -1.0, 0.0);
    glVertex3f (0.5, -1.0, 0.0);
    glVertex3f (1.0, 0.0, 0.0);
    glVertex3f (0.5, 1.0, 0.0);
    glEnd();
}

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);
    renderGrid();
    switch(shape){
        case 0:
            renderTriangle();
            break;
        case 1:
            renderTranslucidTriangle();
            break;
        case 2:
            renderTranslucidTriangle();
            renderTriangleReverse();
            break;
        case 3:
            renderForm();
            break;
    }

    glutSwapBuffers ();
}


void init (void)
{
    // selecionar cor de fundo (preto)
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
    glLoadIdentity();
    glOrtho(-1.2, 1.2, -1.2, 1.2, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
    glLoadIdentity();           // Inicializa com matriz identidade
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}
