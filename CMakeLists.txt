cmake_minimum_required(VERSION 3.0)

project(fluffy_adventure)

include_directories(include extern/libattopng)

set(LIBATTOPNG extern/libattopng/libattopng.h extern/libattopng/libattopng.c)

add_executable(fluffy_adventure ${LIBATTOPNG} main.c src/cell.c src/grid.c src/bin_tree.c src/sidewinder.c)
