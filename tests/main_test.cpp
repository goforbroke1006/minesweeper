//
// Created by goforbroke on 09.03.18.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

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

    REQUIRE(get_rect(5, 4, 4, 100, 100, 2)->getX() == 26);
    REQUIRE(get_rect(5, 4, 4, 100, 100, 2)->getY() == 26);

//    REQUIRE(get_rect(14, 4, 4, 100, 100, 2)->getX() == 76);
//    REQUIRE(get_rect(14, 4, 4, 100, 100, 2)->getX() == 76);
//    REQUIRE(get_rect(14, 4, 4, 100, 100, 2)->getX() == 76);
}