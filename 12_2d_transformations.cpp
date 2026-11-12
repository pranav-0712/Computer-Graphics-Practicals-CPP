#include <GL/glut.h>
#include <cmath>

float ox[3] = {40, 120, 80}, oy[3] = {40, 40, 110};
float x[3] = {40, 120, 80}, y[3] = {40, 40, 110};

void draw(float a[], float b[]) {
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 3; i++)
        glVertex2f(a[i], b[i]);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
    glVertex2i(-250, 0);
    glVertex2i(250, 0);
    glVertex2i(0, -250);
    glVertex2i(0, 250);
    glEnd();

    draw(ox, oy);
    glColor3f(1, 0, 0);
    draw(x, y);
    glFlush();
}

void keyboard(unsigned char key, int mx, int my) {
    float t = 45 * 3.14159 / 180, xr = 40, yr = 40;

    for (int i = 0; i < 3; i++) {
        float a = ox[i], b = oy[i];

        if (key == 's') {
            x[i] = a * 2;
            y[i] = b * 2;
        }

        if (key == 'r') {
            x[i] = xr + (a - xr) * cos(t) - (b - yr) * sin(t);
            y[i] = yr + (a - xr) * sin(t) + (b - yr) * cos(t);
        }

        if (key == 'x') {
            x[i] = a;
            y[i] = -b;
        }

        if (key == 'y') {
            x[i] = -a;
            y[i] = b;
        }
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformations");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
