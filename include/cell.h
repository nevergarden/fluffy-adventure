#ifndef FLUFFY_ADV_CELL_H
#define FLUFFY_ADV_CELL_H

#include <stdbool.h>

typedef struct fa_cell {
  int id;
  int row;
  int column;
  int links;
  int neighbors[4];
} fa_cell_t;

enum relation {
  NORTH = 0b0001,
  SOUTH = 0b0010,
  EAST = 0b0100,
  WEST = 0b1000,
};

fa_cell_t *fa_cell_init(int id, int row, int column, fa_cell_t *cell);
void fa_cell_set_neighbor(fa_cell_t *cell1, enum relation rel,
                          fa_cell_t *cell2);
int fa_cell_link(fa_cell_t *cell1, fa_cell_t *cell2);
void fa_cell_free(fa_cell_t *cell);

bool fa_cell_has_north_link(fa_cell_t *cell);
bool fa_cell_has_south_link(fa_cell_t *cell);
bool fa_cell_has_east_link(fa_cell_t *cell);
bool fa_cell_has_west_link(fa_cell_t *cell);

#endif
