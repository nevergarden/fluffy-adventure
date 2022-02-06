#include "cell.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

fa_cell_t *fa_cell_init(int id, int row, int column, fa_cell_t *cell) {
  if (cell == NULL) cell = malloc(sizeof(fa_cell_t));

  cell->id = id;
  cell->row = row;
  cell->column = column;
  cell->links = 0x0;
  for (size_t i = 0; i < 4; i++) cell->neighbors[i] = -1;
  return cell;
}

#define f_is_neighbor(side, val)                             \
  bool is_##side##_neighbor(fa_cell_t *cell1, int cell2ID) { \
    if (cell1->neighbors[(val)] == cell2ID) return true;     \
    return false;                                            \
  }

f_is_neighbor(north, 0);
f_is_neighbor(south, 1);
f_is_neighbor(east, 2);
f_is_neighbor(west, 3);

#undef f_is_neighbor

void fa_cell_set_neighbor(fa_cell_t *cell1, enum relation rel,
                          fa_cell_t *cell2) {
  switch (rel) {
    case NORTH:
      cell1->neighbors[0] = cell2->id;
      cell2->neighbors[1] = cell1->id;
      break;
    case SOUTH:
      cell1->neighbors[1] = cell2->id;
      cell2->neighbors[0] = cell1->id;
      break;
    case EAST:
      cell1->neighbors[2] = cell2->id;
      cell2->neighbors[3] = cell1->id;
      break;
    case WEST:
      cell1->neighbors[3] = cell2->id;
      cell2->neighbors[2] = cell1->id;
      break;
  }
}

int get_neighbor(fa_cell_t *cell1, int cell2ID) {
  if (is_north_neighbor(cell1, cell2ID)) return 0;
  if (is_south_neighbor(cell1, cell2ID)) return 1;
  if (is_east_neighbor(cell1, cell2ID)) return 2;
  if (is_west_neighbor(cell1, cell2ID)) return 3;
  return -1;
}

int fa_cell_link(fa_cell_t *cell1, fa_cell_t *cell2) {
  int neighborCell = get_neighbor(cell1, cell2->id);
  // north = 1 , south = 2 , east = 4, west = 8
  switch (neighborCell) {
    case 0:
      cell1->links |= 1;
      cell2->links |= 2;
      break;
    case 1:
      cell1->links |= 2;
      cell2->links |= 1;
      break;
    case 2:
      cell1->links |= 4;
      cell2->links |= 8;
      break;
    case 3:
      cell1->links |= 8;
      cell2->links |= 4;
      break;
  }
  return -1;
}

bool fa_cell_has_north_link(fa_cell_t *cell) { return (cell->links & 1) == 1; }

bool fa_cell_has_south_link(fa_cell_t *cell) { return (cell->links & 2) == 2; }

bool fa_cell_has_east_link(fa_cell_t *cell) { return (cell->links & 4) == 4; }

bool fa_cell_has_west_link(fa_cell_t *cell) { return (cell->links & 8) == 8; }

void fa_cell_free(fa_cell_t *cell) { free(cell); }
