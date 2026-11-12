#include <GL/glut.h>
#include <iostream>

using namespace std;

int cx, cy, cr;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void circle(int xc, int yc, int r) {
    int x = 0, y = r, d = 3 - 2 * r;

    while (x <= y) {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);
        plot(xc + y, yc + x);
        plot(xc - y, yc + x);
        plot(xc + y, yc - x);
        plot(xc - y, yc - x);

        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glVertex2i(-250, 0);
    glVertex2i(250, 0);
    glVertex2i(0, -250);
    glVertex2i(0, 250);
    glEnd();

    circle(cx, cy, cr);
    circle(cx + cr, cy, cr);
    circle(cx - cr, cy, cr);
    circle(cx, cy + cr, cr);
    circle(cx, cy - cr, cr);
    glFlush();
}

int main(int argc, char **argv) {
    cout << "Enter center x, center y, radius: ";
    cin >> cx >> cy >> cr;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Circle");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
