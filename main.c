#include <stdio.h>

#include "bin_tree.h"
#include "cell.h"
#include "grid.h"
#include "png_printer.h"

int main() {
  fa_grid_t* grid = fa_grid_init(50, 30);

  fa_bin_tree_on_grid(grid);
  fa_grid_to_png(grid, 10, "maze.png");
  fa_grid_free(grid);
  return 0;
}
