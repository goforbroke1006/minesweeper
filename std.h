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

class Rectangle {
private:
    int x, y, w, h;
public:
//    Rectangle() {}

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

int coord2pos(int colsCount, int row, int col) {
    return row * colsCount + col;
}

int myRand(int from, int to) {
    return rand() % to + from;
}

int get_row_pos(const int pos, const int colsCount) {
    int lp = pos + 1;
    return lp / colsCount + (lp % colsCount > 0 ? 1 : 0) - 1;
}

int get_col_pos(const int pos, const int colsCount) { return pos % colsCount; }

Rectangle *get_rect(
        const int position,
        const int rowsCount, const int colsCount,
        const int screenWidth, const int screenHeght,
        const int margin
) {
    const int cw = screenWidth / colsCount;
    const int ch = screenHeght / rowsCount;

    const int
            x = get_col_pos(position, colsCount),
            y = get_row_pos(position, colsCount);

    int left = x * cw + margin / 2;
    int top = y * ch + margin / 2;

    return new Rectangle(
            left,
            top,
            cw - margin,
            ch - margin
    );
}

#endif //MINESWEEPER_STD_H
