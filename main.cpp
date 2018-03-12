#include <iostream>

#if defined(linux) || defined(_WIN32)

#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <cstring>
#include <sys/ptrace.h>

#else
#include <GLUT/GLUT.h>
#endif

#include "std.h"
#include "extra_glut.h"
#include "field.h"

bool MDEBUG = false;
//#ifdef _DEBUG
//#ifdef NDEBUG
#if defined(_DEBUG) || defined(NDEBUG)
MDEBUG = true;
#endif

bool alive = true;

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

static const int GRID_COLS = 40;
static const int GRID_ROWS = 30;
static const int GRID_CELL_SPACING = 2;


std::vector<CellState *> cells;

void display();

void resize(int width, int height);

void mouseClicks(int button, int state, int x, int y);


void drawCell(int position, CellState *cellState) {
    auto r = get_rect(position,
                      GRID_ROWS, GRID_COLS,
                      SCREEN_WIDTH, SCREEN_HEIGHT,
                      GRID_CELL_SPACING);

    GLfloat red = 1.0, green = 1.0, blue = 1.0;

    if (MDEBUG && cellState->isClosed() && cellState->isHasBomb()) {
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

    drawRect(r->getX(), r->getY(), r->getW(), r->getH(),
             red, green, blue);

    if (!cellState->isClosed() && cellState->isHasBomb()) {
        glColor3f(0.25, 0.25, 0.25);
        drawCircle(r->getX() + r->getW() / 2,
                   r->getY() + r->getH() / 2,
                   std::min(r->getW() / 4, r->getH() / 4),
                   15);
    }

    delete r;
}

void glSprint(int x, int y, char *st) {
    int l, i;

    l = std::strlen(st); // see how many characters are in text string.
    glRasterPos2i(x, y); // location to start printing text
    for (i = 0; i < l; i++) // loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]); // Print a character on the screen
    }
}

bool isDebug() {
    return ptrace(PTRACE_TRACEME, 0, 1, 0) == -1;
}

int main(int argc, char **argv) {
    if (isDebug()) {
        MDEBUG = true;
    }

    srand(time(NULL));

    for (int i = 0; i < GRID_ROWS * GRID_COLS; i++) {
        cells.push_back(new CellState);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Minesweeper");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 1.0);

    generateBombs(cells, 500);

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseClicks);
    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.85, 0.85, 0.85);

    for (unsigned long i = 0; i < GRID_ROWS * GRID_COLS; i++) {
        CellState *state = cells.at(i);
        drawCell(i, state);
    }

    if (!alive) {
        int w4 = SCREEN_WIDTH / 4, h4 = SCREEN_HEIGHT / 4;
        int w2 = SCREEN_WIDTH / 2;
        int h2 = SCREEN_HEIGHT / 2;
        drawRect(w4, h4, w2, h2,
                 0, 0, 0);

        glColor3f(1.0, 0.25, 0.25);
        glSprint(SCREEN_WIDTH / 2 - 75, h2 + 10, const_cast<char *>("GAME OVER"));
    }

    glFlush();
}

void resize(int width, int height) {
    glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void mouseClicks(int button, int state, int x, int y) {
    if (!alive) return;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int cellWidth = SCREEN_WIDTH / GRID_COLS;
        int cellHeight = SCREEN_HEIGHT / GRID_ROWS;

        int row = y / cellHeight;
        int col = x / cellWidth;

        int pos = coord2pos(GRID_COLS, row, col);
        alive = touchCell(cells, pos);

//        auto n = getNearest(pos, GRID_COLS, GRID_ROWS);
//        for (auto it = n.begin(); it != n.end(); it++) {
//            CellState *nc = cells.at(*it);
//            if (!nc->isHasBomb()) {
//                nc->setClosed(false);
//            }
//        }

        auto *excluded = new std::set<int>;
        excluded->insert(pos);
        openClosestRecursively(cells, pos, GRID_COLS, GRID_ROWS, excluded);
        delete excluded;

        std::cout << "Click on " << x << ":" << y << ", " << col << ":" << row << std::endl;
        glutPostRedisplay();
    }
}