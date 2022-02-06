#include <time.h>
#include <stdlib.h>
#include <malloc.h>

#include "sidewinder.h"

typedef struct sized_array {
  int size;
  fa_cell_t ** cells;
} sized_array_t;

sized_array_t * sized_array_init() {
  sized_array_t * array = (sized_array_t*) malloc(sizeof(sized_array_t));
  array->size = 0;
  array->cells = malloc(0);
  return array;
}

void sized_array_add_cell(fa_cell_t * cell, sized_array_t * sized_array) {
  sized_array->cells = realloc(sized_array->cells, sizeof(fa_cell_t)*(sized_array->size+1));
  sized_array->cells[sized_array->size] = cell;
  sized_array->size += 1;
}

fa_cell_t * sized_array_sample(sized_array_t * sized_array) {
  int index = rand()%sized_array->size;
  fa_cell_t * cell = sized_array->cells[index];

  if(sized_array->size == 1)
    return sized_array->cells[0];
  return sized_array->cells[rand()%(sized_array->size-1)];
}

void sized_array_clear(sized_array_t * sized_array) {
  free(sized_array->cells);
  sized_array->size = 0;
  sized_array->cells = malloc(0);
}

void sized_array_free(sized_array_t * sized_array) {
  free(sized_array->cells);
  free(sized_array);
}

void fa_sidewinder(fa_grid_t * grid) {  
  long ltime = time(NULL);
  int stime = (unsigned)ltime;
  srand(stime);

  sized_array_t * run = sized_array_init();

  for (size_t i = 0; i < grid->row_count; i++) {
    sized_array_clear(run);
    for (size_t j = 0; j < grid->column_count; j++) {
      sized_array_add_cell(fa_grid_get_cell(grid, i, j), run);
      fa_cell_t * cell = fa_grid_get_cell(grid, i, j);
      bool eastern_boundary = (cell->neighbors[2] == -1);
      bool northern_boundary = (cell->neighbors[0] == -1);

      bool should_close_out = eastern_boundary || (!northern_boundary && rand()%2 == 0);

      if(should_close_out) {
        fa_cell_t * member = sized_array_sample(run);
        if(member->neighbors[0]!=-1)
          fa_cell_link(member, grid->cells[member->neighbors[0]]);
        sized_array_clear(run);
      }
      else {
        fa_cell_link(cell, grid->cells[cell->neighbors[2]]);
      }
    }
  }
  sized_array_free(run);
}