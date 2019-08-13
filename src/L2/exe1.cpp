#include <GL/glut.h>
#include <iostream>

using namespace std;

void keyboardPress(unsigned char key, int x, int y);

void display(void);

void init(void);


int bolaX = 0, bolaY = 0;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Chess");
    init();
    cout << "Use WASD para movimentar" << endl;
    glutDisplayFunc(display);
    glutKeyboardFunc( keyboardPress );
    glutMainLoop();

    return 0;
}


void display(void) {
    // Limpar todos os pixels
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Inicializa com matriz identidade

//    desenhaEixos();

    glColor3f(1.0, 1.0, 1.0);

    bool par = false;
    for (float i = -2.5; i < 3; i+=2) {
        for (float j = -2.5; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i + (par ? 1 : 0), j, 0.0);
            glutSolidCube(1);
            glPopMatrix();
            par = !par;
        }
    }

    glColor3f(1, 0,0);
    glPushMatrix();
    glTranslatef(bolaX-2.5, bolaY -2.5, 0);
    glutSolidSphere(0.45, 20, 20);
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

// Keyboard callback
void keyboardPress(unsigned char key, int x, int y)
{

    switch (key)
    {
        case 'w' :
            bolaY++;
            break;

        case 'a' :
            bolaX--;
            break;
        case 's' :
            bolaY--;
            break;

        case 'd' :
            bolaX++;
            break;
    }
    if(bolaX < 0)
        bolaX = 0;
    if(bolaX > 5)
        bolaX = 5;

    if(bolaY < 0)
        bolaY = 0;
    if(bolaY > 5)
        bolaY = 5;

    glutPostRedisplay();
}


void init(void) {
    // selecionar cor de fundo (preto)
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
