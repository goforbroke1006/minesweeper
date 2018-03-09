//
// Created by goforbroke on 09.03.18.
//

#ifndef MINESWEEPER_STD_H
#define MINESWEEPER_STD_H

class CellState {
private:
    bool closed;
    bool hasBomb;
public:
    CellState() {
        this->closed = true;
        this->hasBomb = false;
    }

    CellState(bool closed, bool hasBomb) : closed(closed), hasBomb(hasBomb) {}

    bool isClosed() const {
        return closed;
    }

    void setClosed(bool closed) {
        CellState::closed = closed;
    }

    bool isHasBomb() const {
        return hasBomb;
    }

    void setHasBomb(bool hasBomb) {
        CellState::hasBomb = hasBomb;
    }
};

int coord2pos(int colsCount, int row, int col) {
    return row * colsCount + col;
}

int myRand(int from, int to) {
    return rand() % to + from;
}

class Rectangle {
private:
    int x, y, w, h;
public:
    Rectangle() {}

    Rectangle(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

    int getX() const {
        return x;
    }

    void setX(int x) {
        Rectangle::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        Rectangle::y = y;
    }

    int getW() const {
        return w;
    }

    void setW(int w) {
        Rectangle::w = w;
    }

    int getH() const {
        return h;
    }

    void setH(int h) {
        Rectangle::h = h;
    }
};

int get_row_pos(int pos, int colsCount) { return pos / colsCount + (pos % colsCount > 0 ? 1 : 0); }

int get_col_pos(int pos, int colsCount) { return pos % colsCount; }

Rectangle *get_rect(
        int position,
        int rowsCount, int colsCount,
        int screenWidth, int screenHeght,
        int margin
) {
    int cellWidth = screenWidth / colsCount;
    int cellHeight = screenHeght / rowsCount;

    int
            x = get_col_pos(position, colsCount),
            y = get_row_pos(position, colsCount);

    int left = x * cellWidth + margin / 2;
    int top = y * cellHeight + margin / 2;

    return new Rectangle(
            left,
            top,
            cellWidth - margin,
            cellHeight - margin
    );
}

#endif //MINESWEEPER_STD_H
