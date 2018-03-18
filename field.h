//
// Created by goforbroke on 12.03.18.
//

#ifndef MINESWEEPER_FIELD_H
#define MINESWEEPER_FIELD_H

#include <iostream>
#include <vector>
#include <set>

#include "std.h"

void generateBombs(std::vector<CellState *> field, const unsigned long count) {
    for (int i = 0; i < count; i++) {
        long cpos = myRand(0, field.size());
        auto *state = field.at(cpos);
        state->setHasBomb(true);
        field.push_back(state);
    }
}

bool touchCell(std::vector<CellState *> field, const unsigned long pos) {
    CellState *c = field.at(pos);
    if (c->isHasBomb()) {
        return false;
    }
    c->setClosed(false);
    return true;
}

void openClosestRecursively(
        std::vector<CellState *> field,
        const long pos,
        const int colsCount, const int rowsCount,
        std::set<long> *excluded
) {
    auto n = getNearest(pos, colsCount, rowsCount);
    for (auto it = n.begin(); it != n.end(); it++) {
        const long &npos = *it;
        if (NULL_CELL == npos
            || npos >= field.size()
            || excluded->find(npos) != excluded->end()) {
            continue;
        }
        
        CellState *nc = field.at(npos);
        if (!nc->isHasBomb()) {
            nc->setClosed(false);
            excluded->insert(npos);
            openClosestRecursively(field, npos, colsCount, rowsCount, excluded);
        }
    }
}

#endif //MINESWEEPER_FIELD_H
