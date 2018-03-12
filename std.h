//
// Created by goforbroke on 09.03.18.
//

#ifndef MINESWEEPER_STD_H
#define MINESWEEPER_STD_H

#include <iterator>
#include <sstream>

static const int NULL_CELL = -1;

std::string implode(const std::vector<int> v1, const char *delimiter) {
    std::ostringstream oss;
    std::copy(
            v1.begin(),
            v1.end() - 1,
            std::ostream_iterator<int>(oss, delimiter)
    );
    oss << v1.back();
    return oss.str();
}

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

int coord2pos(const int colsCount, const int row, const int col) {
    return row * colsCount + col;
}

int myRand(const int from, const int to) {
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

std::vector<int> getNearest(const int pos,
                            const int colsCount, const int rowsCount) {
    std::vector<int> res;

    int n = pos - colsCount > 0
            ? (pos - colsCount)
            : NULL_CELL;
    res.push_back(n);

    int ne = (pos + 1 > colsCount && pos % colsCount < colsCount
              ? (pos - colsCount + 1)
              : NULL_CELL);
    res.push_back(ne);

    int e = (pos % colsCount + 1 < colsCount)
            ? (pos + 1)
            : NULL_CELL;
    res.push_back(e);

    int tmp_se = pos + colsCount + 1;
    int se = (
                     tmp_se <= colsCount * rowsCount - 1
                     && tmp_se % colsCount > pos % colsCount
             )
             ? tmp_se
             : NULL_CELL;
    res.push_back(se);

    int s = (pos + colsCount < colsCount * rowsCount - 1)
            ? pos + colsCount
            : NULL_CELL;
    res.push_back(s);

    int tmp_sw = pos + colsCount - 1;
    int sw = tmp_sw >= 0 && tmp_sw % colsCount < pos % colsCount
             ? tmp_sw
             : NULL_CELL;
    res.push_back(sw);

    int w = (pos % colsCount > 0) ? (pos - 1) : NULL_CELL;
    res.push_back(w);

    // TODO: nw
    int tmp_nw = pos - colsCount - 1;
    int nw = tmp_nw >= 0 && tmp_nw % colsCount < pos % colsCount
             ? tmp_nw
             : NULL_CELL;
    res.push_back(nw);

    return res;
}

#endif //MINESWEEPER_STD_H
