//
// Created by goforbroke on 17.03.18.
//

#ifndef MINESWEEPER_DUMP_H
#define MINESWEEPER_DUMP_H

#include "std.h"

void dump_generateBombs(std::vector<CellState *> field) {
    std::vector<long> c = {
            0, 1, 2, 3, 4, 5, 6, 7,
            47, 87, 127, 167, 207, 247,
            246, 245, 244, 243, 242, 241, 240,
            240, 200, 160, 120, 80, 40,

            10, 11,
            12, 52,
            92, 91,
            90, 50
    };


    for (auto it = c.begin(); it != c.end(); it++) {
        auto *state = field.at(*it);
        state->setHasBomb(true);
        field.push_back(state);
    }
}

#endif //MINESWEEPER_DUMP_H
