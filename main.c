#include <stdio.h>

#include "cell.h"
#include "grid.h"

int main() {
  fa_grid_t* grid = fa_grid_init(4, 4);
  for (int j = 0; j < 16; j++) {
    for (int i = 0; i < 4; i++) {
      printf("%d, ", grid->cells[j]->neighbors[i]);
    }
    printf("\n");
  }

  fa_cell_t* cell = fa_grid_get_cell(grid, 1, 2);
  printf("%d\n", cell->id);
  fa_grid_free(grid);
  return 0;
}
