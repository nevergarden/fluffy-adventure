#include "grid.h"

void set_cell_neighbors(fa_grid_t* grid, int id, int row, int col) {
  if (row - 1 >= 0) {
    grid->cells[id]->neighbors[0] = (row - 1) * grid->row_count + col;
  }
  if (row + 1 < grid->row_count) {
    grid->cells[id]->neighbors[1] = (row + 1) * grid->row_count + col;
  }
  if (col + 1 < grid->column_count) {
    grid->cells[id]->neighbors[2] = row * grid->row_count + (col + 1);
  }
  if (col - 1 >= 0) {
    grid->cells[id]->neighbors[3] = row * grid->row_count + (col - 1);
  }
}

void configure_cells(fa_grid_t* grid) {
  for (size_t row = 0; row < grid->row_count; row++) {
    for (size_t column = 0; column < grid->column_count; column++) {
      int id = row * grid->row_count + column;
      grid->cells[id] = fa_cell_init(id, row, column, NULL);
    }
  }

  for (size_t row = 0; row < grid->row_count; row++) {
    for (size_t column = 0; column < grid->column_count; column++) {
      int id = row * grid->row_count + column;
      set_cell_neighbors(grid, id, row, column);
    }
  }
}

fa_grid_t* fa_grid_init(size_t row_count, size_t column_count) {
  fa_grid_t* grid = malloc(sizeof(fa_grid_t));
  grid->row_count = row_count;
  grid->column_count = column_count;
  grid->cells = malloc(sizeof(fa_cell_t) * row_count * column_count);
  configure_cells(grid);
  return grid;
}

void fa_grid_free(fa_grid_t* grid) {
  for (size_t i = 0; i < grid->row_count * grid->column_count; i++)
    fa_cell_free(grid->cells[i]);

  free(grid->cells);
  free(grid);
}
