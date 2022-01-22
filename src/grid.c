#include "grid.h"

#include <string.h>

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

int get_string_size_from_grid(fa_grid_t * grid) {
  return (grid->column_count*4+2)*3*grid->row_count;
}

void fa_grid_to_string(fa_grid_t* grid) {
  int string_count = get_string_size_from_grid(grid);
  char maze_string[string_count];
  int seperator_size = grid->column_count*4+3;
  char seperator[seperator_size+1];
  char body[3] = "   ";
  char top[1] = "|";
  char bottom[1] = "+";
  
  strcat(seperator, "+");
  for (size_t i = 0; i < grid->column_count; i++)
    strcat(seperator, "---+");
  strcat(seperator, "\n");
  strcat(seperator, "\0");
  printf("%s", seperator);
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
  fa_grid_to_string(grid);
  for (size_t i = 0; i < grid->row_count * grid->column_count; i++)
    fa_cell_free(grid->cells[i]);

  free(grid->cells);
  free(grid);
}

// Will return a cell / NULL if not found
fa_cell_t* fa_grid_get_cell(fa_grid_t* grid, int row, int col) {
  if (col <= grid->column_count && row <= grid->row_count)
    return grid->cells[(row * grid->row_count) + col];
  return NULL;
}