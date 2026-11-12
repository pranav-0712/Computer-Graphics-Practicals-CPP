#include <GL/glut.h>
#include <cstdlib>

int type = 1, clicks = 0, xa, ya;

void plot(int x, int y, int i) {
    if (type == 2 && i % 4 != 0)
        return;

    if (type == 3 && i % 12 >= 7)
        return;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void bresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = x2 > x1 ? 1 : -1, sy = y2 > y1 ? 1 : -1;
    glPointSize(type == 4 ? 4 : 1);

    if (dx >= dy) {
        int p = 2 * dy - dx;

        for (int i = 0; i <= dx; i++) {
            plot(x1, y1, i);
            x1 += sx;

            if (p < 0)
                p += 2 * dy;
            else {
                y1 += sy;
                p += 2 * (dy - dx);
            }
        }
    } else {
        int p = 2 * dx - dy;

        for (int i = 0; i <= dy; i++) {
            plot(x1, y1, i);
            y1 += sy;

            if (p < 0)
                p += 2 * dx;
            else {
                x1 += sx;
                p += 2 * (dx - dy);
            }
        }
    }

    glFlush();
}

void object() {
    bresenham(-100, -100, 100, -100);
    bresenham(100, -100, 100, 50);
    bresenham(100, 50, -100, 50);
    bresenham(-100, 50, -100, -100);
    bresenham(-100, 50, 0, 150);
    bresenham(0, 150, 100, 50);
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
        bresenham(xa, ya, x, y);
        clicks = 0;
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '4')
        type = key - '0';

    if (key == '5')
        object();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Line");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
