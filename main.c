#include <stdio.h>

#include "bin_tree.h"
#include "cell.h"
#include "grid.h"

int main() {
  fa_grid_t* grid = fa_grid_init(5, 5);

  fa_bin_tree_on_grid(grid);
  fa_grid_print(grid);
  fa_grid_free(grid);
  return 0;
}
