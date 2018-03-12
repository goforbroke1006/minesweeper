//
// Created by goforbroke on 12.03.18.
//

#ifndef MINESWEEPER_FIELD_H
#define MINESWEEPER_FIELD_H

#include <iostream>
#include <vector>
#include <set>

#include "std.h"

void generateBombs(std::vector<CellState *> field, const int count) {
    for (int i = 0; i < count;) {
        int cpos = myRand(0, field.size());
        auto *state = field.at(cpos);
        state->setHasBomb(true);
        field.push_back(state);
        i++;
    }
}

bool touchCell(std::vector<CellState *> field, const int pos) {
    CellState *c = field.at(pos);
    if (c->isHasBomb()) {
        std::cout << "YOU ARE DEAD!!!" << std::endl;
        return false;
    }
    c->setClosed(false);
    return true;
}

void openClosestRecursively(
        std::vector<CellState *> field,
        const int pos,
        const int colsCount, const int rowsCount,
        std::set<int> *excluded) {
    auto n = getNearest(pos, colsCount, rowsCount);
    for (auto it = n.begin(); it != n.end(); it++) {
        if (NULL_CELL == *it
            || *it >= field.size()
            || excluded->find(*it) != excluded->end()) {
            continue;
        }

        CellState *nc = field.at(*it);
        if (!nc->isHasBomb()) {
            nc->setClosed(false);
            excluded->insert(*it);

            if (std::distance(n.begin(), it) % 2 == 0) {
                openClosestRecursively(field, *it, colsCount, rowsCount, excluded);
            }
        }
    }
}

#endif //MINESWEEPER_FIELD_H
