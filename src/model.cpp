/**
 * Exercice model
 *
 * Copy this file and add to CMakeLists
 */

#include <stdio.h>
#include <GL/glut.h>

const char TITLE[] = "MODEL";
const float ORTHO[2][2] = {
        {-1, 1},
        {-1, 1}
};

void display(void);
void init (void);
int shape = 0;

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);

    /**
     * YOUR CODE HERE
     */

    glutSwapBuffers ();
}

int main(int argc, char** argv)
{
    printf("%s\n", TITLE);
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (TITLE);
    init ();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}


void init (void)
{
    // BACKGROUND
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
    glLoadIdentity();
    // boundaries
    glOrtho(ORTHO[0][0],ORTHO[0][1],ORTHO[1][0],ORTHO[1][1], -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
    glLoadIdentity();           // Inicializa com matriz identidade
}
