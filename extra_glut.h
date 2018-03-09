//
// Created by goforbroke on 09.03.18.
//

#ifndef MINESWEEPER_DRAW_H
#define MINESWEEPER_DRAW_H

#if defined(linux) || defined(_WIN32)

#include <GL/glut.h>

#else
#include <GLUT/GLUT.h>
#endif

#include <cmath>

void drawCircle(int cx, int cy, int radius, int sidesCount) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    GLfloat x2, y2;
    double step = (2 * M_PI) / sidesCount;
    for (float angle = 0.0f; angle <= 2 * M_PI + step;) {
        x2 = cx + std::sin(angle) * radius;
        y2 = cy + std::cos(angle) * radius;
        glVertex2f(x2, y2);
        angle += step;
    }
    glEnd();
}

void drawRect(int x, int y, int w, int h,
              GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);

    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + w, y, 0.0);
    glVertex3f(x + w, y + h, 0.0);
    glVertex3f(x, y + h, 0.0);
    glEnd();
}

#endif //MINESWEEPER_DRAW_H
