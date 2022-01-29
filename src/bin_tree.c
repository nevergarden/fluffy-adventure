#include "bin_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cell.h"
#include "grid.h"

void fa_bin_tree_on_grid(fa_grid_t* grid) {
  long ltime = time(NULL);
  int stime = (unsigned)ltime;
  srand(stime);

  for (size_t i = 0; i < grid->column_count * grid->row_count; i++) {
    fa_cell_t* cell = grid->cells[i];
    int neighbors[2] = {cell->neighbors[0], cell->neighbors[3]};

    int count = neighbors[0] == -1 ? 0 : 1;

    if (neighbors[1] != -1) count += 1;
    if (count == 1 && neighbors[1] != -1) neighbors[0] = neighbors[1];
    if (count == 0) continue;

    int randomNumber = rand() % count;
    fa_cell_t* neighbor = grid->cells[neighbors[randomNumber]];
    fa_cell_link(cell, neighbor);
  }
}
