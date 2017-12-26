#include <iostream>

#if defined(linux) || defined(_WIN32)

#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <cstring>

#else
#include <GLUT/GLUT.h>
#endif

const bool DEBUG = true;

bool alive = true;

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

static const int GRID_COLS = 40;
static const int GRID_ROWS = 30;
static const int GRID_CELL_SPACING = 2;

struct CellState {
    bool closed = true;
    bool hasBomb = false;
};

std::map<int, CellState> cellsMeta;

void display();

void resize(int width, int height);

void mouseClicks(int button, int state, int x, int y);

int coord2pos(int row, int col) {
    return row * GRID_COLS + col;
}

//std::tuple<int, int> pos2coord(int pos) {
//    int row = pos / GRID_ROWS;
//    int col = pos - row * GRID_ROWS;
//    return std::make_tuple(row, col);
//}

int myRand(int from, int to) {
    return rand() % to + from;
}

int getRandCell() {
    return coord2pos(
            myRand(0, GRID_ROWS - 1),
            myRand(0, GRID_COLS - 1)
    );
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

void drawCell(int x, int y, CellState cellState) {
    int cellWidth = SCREEN_WIDTH / GRID_COLS;
    int cellHeight = SCREEN_HEIGHT / GRID_ROWS;

    int left = x * cellWidth + GRID_CELL_SPACING / 2;
    int top = y * cellHeight + GRID_CELL_SPACING / 2;
    int right = left + cellWidth - GRID_CELL_SPACING;
    int bottom = top + cellHeight - GRID_CELL_SPACING;

    if (DEBUG && cellState.closed && cellState.hasBomb) {
        glColor3f(1.0, 0.75, 0.75);
    } else if (cellState.closed) {
        glColor3f(0.75, 0.75, 0.75);
    } else if (cellState.hasBomb) {
        glColor3f(1.0, 0.0, 0.0);
    } else {
        glColor3f(1.0, 1.0, 1.0);
    }

    glBegin(GL_POLYGON);
    glVertex3f(left, top, 0.0);
    glVertex3f(right, top, 0.0);
    glVertex3f(right, bottom, 0.0);
    glVertex3f(left, bottom, 0.0);
    glEnd();

    if (!cellState.closed && cellState.hasBomb) {
        glColor3f(0.25, 0.25, 0.25);
        drawCircle(left + cellWidth / 2, top + cellHeight / 2, std::min(cellWidth / 4, cellHeight / 4), 15);
    }
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

int main(int argc, char **argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Minesweeper");

    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
    glMatrixMode(GL_PROJECTION);              // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 1.0);   // setup a 10x10x2 viewing world

    // Generate bombs
    for (int i = 0; i < 10;) {
        int cpos = getRandCell();
        if (cellsMeta.find(cpos) == cellsMeta.end()) {
            std::cout << "Create bomb in cell # " << cpos << std::endl;

            CellState state;
            state.hasBomb = true;
            cellsMeta.insert(std::pair<int, CellState>(cpos, state));
            i++;
        }
    }

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseClicks);
    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.85, 0.85, 0.85);

    int pos = 0;

    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            if (cellsMeta.find(pos) == cellsMeta.end()) {
                cellsMeta.insert(std::pair<int, CellState>(pos, CellState{}));
            }
            CellState &state = cellsMeta.at(pos);
            drawCell(x, y, state);
            pos++;
        }
    }

    if (!alive) {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex3f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0.0);
        glVertex3f(SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 4, 0.0);
        glVertex3f(SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 4 * 3, 0.0);
        glVertex3f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 * 3, 0.0);
        glEnd();

        glColor3f(1.0, 0.25, 0.25);
        glSprint(SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 10, const_cast<char *>("GAME OVER"));
    }

    glFlush();
}

void resize(int width, int height) {
//    glutReshapeWindow(SCREEN_WIDTH, SCREEN_TOP_MARGIN + SCREEN_HEIGHT);
    glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void mouseClicks(int button, int state, int x, int y) {
    if (!alive) return;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int cellWidth = SCREEN_WIDTH / GRID_COLS;
        int cellHeight = SCREEN_HEIGHT / GRID_ROWS;

        int row = y / cellHeight;
        int col = x / cellWidth;

        int pos = coord2pos(row, col);
        CellState &cellState = cellsMeta.at(pos);
        if (cellState.hasBomb) {
            std::cout << "YOU ARE DEAD!!!" << std::endl;
            alive = false;
        }
        cellState.closed = false;

        std::cout << "Click on " << x << ":" << y << ", " << col << ":" << row << std::endl;
        glutPostRedisplay();
    }
}