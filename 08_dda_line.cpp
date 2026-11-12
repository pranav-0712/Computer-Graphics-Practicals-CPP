#include <GL/glut.h>
#include <cmath>

int type = 1, clicks = 0, xa, ya;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void dda(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1, dy = y2 - y1;
    int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float xi = dx / steps, yi = dy / steps;
    glPointSize(type == 4 ? 4 : 1);

    for (int i = 0; i <= steps; i++) {
        if (type == 1 || type == 4)
            plot(round(x1), round(y1));

        if (type == 2 && i % 4 == 0)
            plot(round(x1), round(y1));

        if (type == 3 && i % 12 < 7)
            plot(round(x1), round(y1));

        x1 += xi;
        y1 += yi;
    }

    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glVertex2i(-250, 0);
    glVertex2i(250, 0);
    glVertex2i(0, -250);
    glVertex2i(0, 250);
    glEnd();

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;

    x = x - 250;
    y = 250 - y;

    if (clicks == 0) {
        xa = x;
        ya = y;
        clicks = 1;
    } else {
        dda(xa, ya, x, y);
        clicks = 0;
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '4')
        type = key - '0';
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
