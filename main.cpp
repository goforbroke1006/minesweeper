#include <iostream>

#if defined(linux) || defined(_WIN32)

#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <sys/ptrace.h>

#else
#include <GLUT/GLUT.h>
#endif

#include "std.h"
#include "extra_glut.h"
#include "field.h"
#include "dump.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

static const int GRID_COLS = 40;
static const int GRID_ROWS = 30;
static const int GRID_CELL_SPACING = 2;

bool debug = false;
bool alive = true;
bool win = false;
std::vector<CellState *> cells;

void display();

void resize(int width, int height);

void mouseClicks(int button, int state, int x, int y);

bool isDebug() {
#if defined(_DEBUG) || defined(NDEBUG)
    return true;
#endif
    return ptrace(PTRACE_TRACEME, 0, 1, 0) == -1;
}

int main(int argc, char **argv) {
    if (isDebug()) {
        debug = true;
    }

    unsigned short bombsCount = 400;
    if (argc >= 2) {
        bombsCount = atoi(argv[1]);
    }

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

    generateBombs(cells, bombsCount);

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
        auto r = get_rect(i,
                          GRID_ROWS, GRID_COLS,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          GRID_CELL_SPACING);
        short bc = getBombsCount(cells, i, GRID_COLS, GRID_ROWS);
        drawCell(i, state, r, bc, debug);
    }

    if (!alive) {
        int w4 = SCREEN_WIDTH / 4, h4 = SCREEN_HEIGHT / 4;
        int w2 = SCREEN_WIDTH / 2;
        int h2 = SCREEN_HEIGHT / 2;
        drawRect(w4, h4, w2, h2,
                 0, 0, 0);

        glColor3f(1.0, 0.25, 0.25);
        drawText(SCREEN_WIDTH / 2 - 75, h2 + 10, "GAME OVER");
    }

    if (win) {
        int w4 = SCREEN_WIDTH / 4, h4 = SCREEN_HEIGHT / 4;
        int w2 = SCREEN_WIDTH / 2;
        int h2 = SCREEN_HEIGHT / 2;
        drawRect(w4, h4, w2, h2,
                 0, 0, 0);

        glColor3f(0.25, 1.0, 0.25);
        drawText(SCREEN_WIDTH / 2 - 80, h2 + 10, "!!!YOU WIN!!!");
    }

    glFlush();
}

void resize(int width, int height) {
    glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void mouseClicks(int button, int state, int x, int y) {
    if (!alive) return;
    if (win) return;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int cellWidth = SCREEN_WIDTH / GRID_COLS;
        int cellHeight = SCREEN_HEIGHT / GRID_ROWS;

        int row = y / cellHeight;
        int col = x / cellWidth;

        long pos = coord2pos(GRID_COLS, row, col);
        alive = touchCell(cells, pos);

        if (alive) {
            auto *excluded = new std::set<long>;
            excluded->insert(pos);
            openClosestRecursively(cells, pos, GRID_COLS, GRID_ROWS, excluded);
            delete excluded;
        }

        long c = 0;
        for (CellState *cs : cells) {
            if (!cs->isHasBomb() && cs->isClosed()) c++;
        }
        if (c == 0) win = true;

        std::cout << "Click on " << pos << " - " << x << ":" << y << ", " << col << ":" << row << std::endl;
        glutPostRedisplay();
    }
}