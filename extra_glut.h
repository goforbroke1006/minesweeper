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

void drawText(int x, int y, std::string s,
              void *fontStyle = GLUT_BITMAP_TIMES_ROMAN_24) {
    size_t len = std::strlen(s.c_str());
    glRasterPos2i(x, y);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(fontStyle, s.c_str()[i]);
    }
}

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

void drawCell(const unsigned long position, CellState *cellState, Rectangle &r,
              bool debug = false
) {
    GLfloat red = 1.0, green = 1.0, blue = 1.0;

    if (debug && cellState->isClosed() && cellState->isHasBomb()) {
        green = 0.75;
        blue = 0.75;
    } else if (cellState->isClosed()) {
        red = 0.75;
        green = 0.75;
        blue = 0.75;
    } else if (cellState->isHasBomb()) {
        green = 0.0;
        blue = 0.0;
    }

    drawRect(r.getX(), r.getY(), r.getW(), r.getH(),
             red, green, blue);

    if (!cellState->isClosed() && cellState->isHasBomb()) {
        glColor3f(0.25, 0.25, 0.25);
        drawCircle(r.getX() + r.getW() / 2,
                   r.getY() + r.getH() / 2,
                   std::min(r.getW() / 4, r.getH() / 4),
                   15);
    }
}

#endif //MINESWEEPER_DRAW_H
