//
// Created by goforbroke on 09.03.18.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iterator>
#include "catch.hpp"

#include "../std.h"

TEST_CASE("Position convertation works fine") {
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
    REQUIRE(get_rect(0, 2, 2, 100, 100, 2)->getW() == 48);

    REQUIRE(get_rect(0, 4, 4, 100, 100, 2)->getX() == 1);
    REQUIRE(get_rect(0, 4, 4, 100, 100, 2)->getY() == 1);

    REQUIRE(get_rect(5, 4, 4, 100, 100, 2)->getX() == 26); // rect in position 2x2
    REQUIRE(get_rect(5, 4, 4, 100, 100, 2)->getY() == 26); // rect in position 2x2

    REQUIRE(get_rect(15, 4, 4, 100, 100, 2)->getX() == 76); // rect in position 4x4
    REQUIRE(get_rect(15, 4, 4, 100, 100, 2)->getY() == 76); // rect in position 4x4
}

TEST_CASE("Nearest cells detect correctly") {
    const std::vector<int> &v1 = getNearest(5, 4, 4); // cell 2x2
    REQUIRE(v1 == std::vector<int>{1, 2, 6, 10, 9, 8, 4, 0});
}