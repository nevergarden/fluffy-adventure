#include <stdio.h>

#include "cell.h"
#include "grid.h"
#include "bin_tree.h"

int main() {
  fa_grid_t* grid = fa_grid_init(3, 4);

  // fa_bin_tree_on_grid(grid);
  fa_cell_link(grid->cells[0], grid->cells[1]);
  // fa_cell_link(grid->cells[0], grid->cells[4]);
  // fa_cell_link(grid->cells[4], grid->cells[5]);
  // fa_cell_link(grid->cells[5], grid->cells[6]);
  // fa_cell_link(grid->cells[6], grid->cells[7]);
  // printf("%d\n", grid->cells[6]->links);
  fa_grid_free(grid);
  return 0;
}
