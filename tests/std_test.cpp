//
// Created by goforbroke on 09.03.18.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iterator>
#include "catch.hpp"

#include "../std.h"

TEST_CASE("Position converting works fine") {
    REQUIRE(get_col_pos(5, 4) == 1);
    REQUIRE(get_row_pos(5, 4) == 1);

    REQUIRE(get_row_pos(101, 50) == 2);
    REQUIRE(get_row_pos(99, 50) == 1);
    REQUIRE(get_col_pos(101, 50) == 1);
    REQUIRE(get_col_pos(19, 20) == 19);
    REQUIRE(get_row_pos(0, 50) == 0);
    REQUIRE(get_row_pos(50, 50) == 1);
}

TEST_CASE("Getting rectangle by position works fine") {
    REQUIRE(get_rect(0, 2, 2, 100, 100, 2).getW() == 48);

    REQUIRE(get_rect(0, 4, 4, 100, 100, 2).getX() == 1); // rect in position 1x1 in 4x4-grid
    REQUIRE(get_rect(0, 4, 4, 100, 100, 2).getY() == 1); // rect in position 1x1 in 4x4-grid

    REQUIRE(get_rect(5, 4, 4, 100, 100, 2).getX() == 26); // rect in position 2x2 in 4x4-grid
    REQUIRE(get_rect(5, 4, 4, 100, 100, 2).getY() == 26); // rect in position 2x2 in 4x4-grid

    REQUIRE(get_rect(15, 4, 4, 100, 100, 2).getX() == 76); // rect in position 4x4 in 4x4-grid
    REQUIRE(get_rect(15, 4, 4, 100, 100, 2).getY() == 76); // rect in position 4x4 in 4x4-grid
}

TEST_CASE("Nearest cells detect correctly") {
    REQUIRE(getNearest(5, 4, 4) == std::vector<long>{
            1, 6, 9, 4
    }); // cell 2x2 in 4x4-grid
    REQUIRE(getNearest(0, 4, 4) == std::vector<long>{
            NULL_CELL, 1, 4, NULL_CELL
    }); // cell 1x1 in 4x4-grid

    REQUIRE(getNearest(0, 10, 10) == std::vector<long>{
            NULL_CELL, 1, 10, NULL_CELL
    }); // cell 1x1 in 10x10-grid
    REQUIRE(getNearest(1, 10, 10) == std::vector<long>{
            NULL_CELL, 2, 11, 0
    }); // cell 2x1 in 10x10-grid
    REQUIRE(getNearest(88, 10, 10) == std::vector<long>{
            78, 89, 98, 87
    }); // cell 9x9 in 10x10-grid
    REQUIRE(getNearest(90, 10, 10) == std::vector<long>{
            80, 91, NULL_CELL, NULL_CELL
    }); // cell 1x10 in 10x10-grid
    REQUIRE(getNearest(70, 10, 10) == std::vector<long>{
            60, 71, 80, NULL_CELL
    }); // cell 1x8 in 10x10-grid
    REQUIRE(getNearest(79, 10, 10) == std::vector<long>{
            69, NULL_CELL, 89, 78
    }); // cell 10x8 in 10x10-grid
}