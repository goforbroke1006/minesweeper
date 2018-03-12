cmake_minimum_required(VERSION 3.8)
project(minesweeper)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp std.h extra_glut.h field.h)
add_executable(minesweeper ${SOURCE_FILES})
target_link_libraries(minesweeper glut GLU GL)


add_executable(minesweeper_tests tests/catch.hpp tests/std_test.cpp)