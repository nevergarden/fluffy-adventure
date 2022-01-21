#ifndef FLUFFY_ADV_GRID_H
#define FLUFFY_ADV_GRID_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>  // size_t

#include "cell.h"  // fa_cell_t, fa_cell_init, fal_cell_free

typedef struct fa_grid {
  size_t row_count;
  size_t column_count;
  fa_cell_t** cells;
} fa_grid_t;

fa_grid_t* fa_grid_init(size_t row_count, size_t column_count);
void fa_grid_free(fa_grid_t* grid);
#endif
