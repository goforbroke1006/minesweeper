//
// Created by goforbroke on 09.03.18.
//

#ifndef MINESWEEPER_STD_H
#define MINESWEEPER_STD_H

#include <iterator>
#include <sstream>
#include <random>

static const long NULL_CELL = -1;

std::string implode(const std::vector<int> &v1, const std::string &delimiter) {
    std::ostringstream oss;
    std::copy(
            v1.begin(),
            v1.end() - 1,
            std::ostream_iterator<int>(oss, delimiter.c_str())
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
    long x, y;
    unsigned long w, h;
public:
    Rectangle(long x, long y, unsigned long w, unsigned long h)
            : x(x), y(y), w(w), h(h) {}

    long getX() const {
        return x;
    }

    void setX(long x) {
        Rectangle::x = x;
    }

    long getY() const {
        return y;
    }

    void setY(long y) {
        Rectangle::y = y;
    }

    unsigned long getW() const {
        return w;
    }

    void setW(unsigned long w) {
        Rectangle::w = w;
    }

    unsigned long getH() const {
        return h;
    }

    void setH(unsigned long h) {
        Rectangle::h = h;
    }
};

const unsigned long coord2pos(const int colsCount,
                              const int row, const int col) {
    return static_cast<const unsigned long>(row * colsCount + col);
}

long myRand(const long from, const long to) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<long> dist(from, to);
    return dist(mt);
}

const unsigned long get_row_pos(const unsigned long pos, const int colsCount) {
    unsigned long lp = pos + 1;
    return lp / colsCount + (lp % colsCount > 0 ? 1 : 0) - 1;
}

const unsigned long get_col_pos(const unsigned long pos, const int colsCount) { return pos % colsCount; }

Rectangle get_rect(
        const unsigned long position,
        const int rowsCount, const int colsCount,
        const unsigned long screenWidth, const unsigned long screenHeght,
        const long margin
) {
    const unsigned long cw = screenWidth / colsCount;
    const unsigned long ch = screenHeght / rowsCount;

    const unsigned long
            x = get_col_pos(position, colsCount),
            y = get_row_pos(position, colsCount);

    const unsigned long left = x * cw + margin / 2;
    const unsigned long top = y * ch + margin / 2;

    return {
            left,
            top,
            cw - margin,
            ch - margin
    };
}

std::vector<long> getNearestNESW(const long pos,
                                 const int colsCount, const int rowsCount) {
    std::vector<long> res;

    const long tmp_n = pos - colsCount;
    const long n = tmp_n >= 0
                   ? (pos - colsCount)
                   : NULL_CELL;
    res.push_back(n);

//    const long tmp_ne = pos - colsCount + 1;
//    long ne = tmp_ne >= 0 && tmp_ne % colsCount > pos % colsCount
//              ? (pos - colsCount + 1)
//              : NULL_CELL;
//    res.push_back(ne);

    long e = (pos % colsCount + 1 < colsCount && pos + 1 < rowsCount * colsCount)
             ? (pos + 1)
             : NULL_CELL;
    res.push_back(e);

//    long tmp_se = pos + colsCount + 1;
//    long se =
//            tmp_se <= colsCount * rowsCount - 1
//            && tmp_se % colsCount > pos % colsCount
//            ? tmp_se
//            : NULL_CELL;
//    res.push_back(se);

    long s = (pos + colsCount < colsCount * rowsCount - 1) && pos + colsCount < rowsCount * colsCount
             ? pos + colsCount
             : NULL_CELL;
    res.push_back(s);

//    long tmp_sw = pos + colsCount - 1;
//    long sw = tmp_sw >= 0 && tmp_sw % colsCount < pos % colsCount
//              ? tmp_sw
//              : NULL_CELL;
//    res.push_back(sw);

    long w = (pos % colsCount > 0) ? (pos - 1) : NULL_CELL;
    res.push_back(w);

//    long tmp_nw = pos - colsCount - 1;
//    long nw = tmp_nw >= 0 && tmp_nw % colsCount < pos % colsCount
//              ? tmp_nw
//              : NULL_CELL;
//    res.push_back(nw);

    return res;
}

std::vector<long> getNearestAll(const long pos,
                                const int colsCount, const int rowsCount) {
    std::vector<long> res;

    int total = rowsCount * colsCount;

    auto news = getNearestNESW(pos, colsCount, rowsCount);
    long &n = news.at(0);
    long &e = news.at(1);
    long &s = news.at(2);
    long &w = news.at(3);


    res.push_back(n);

    const long tmp_ne = pos - colsCount + 1;
    long ne = tmp_ne >= 0 && tmp_ne % colsCount > pos % colsCount
              ? (pos - colsCount + 1) : NULL_CELL;
    res.push_back(ne);

    res.push_back(e);

    long tmp_se = pos + colsCount + 1;
    long se = tmp_se <= colsCount * rowsCount - 1
              && tmp_se % colsCount > pos % colsCount
              && tmp_se < total
              ? tmp_se : NULL_CELL;
    res.push_back(se);

    res.push_back(s);

    long tmp_sw = pos + colsCount - 1;
    long sw = tmp_sw >= 0 && tmp_sw % colsCount < pos % colsCount && tmp_sw < total
              ? tmp_sw : NULL_CELL;
    res.push_back(sw);

    res.push_back(w);

    long tmp_nw = pos - colsCount - 1;
    long nw = tmp_nw >= 0 && tmp_nw % colsCount < pos % colsCount
              ? tmp_nw : NULL_CELL;
    res.push_back(nw);


    return res;
}

short getBombsCount(std::vector<CellState *> cells, long pos,
                    const int colsCount, const int rowsCount) {
    short res = 0;
    auto nList = getNearestAll(pos, colsCount, rowsCount);
    for (long &n : nList) {
        if (n == NULL_CELL) continue;
        if (cells.at(n)->isHasBomb()) res++;
    }
    return res;
}

#endif //MINESWEEPER_STD_H
