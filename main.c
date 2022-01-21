#include "cell.h"
#include "grid.h"

#include <stdio.h>

int main()
{
  fa_grid_t * grid = fa_grid_init(4, 4);
  for(int j = 0; j < 16; j++)
  {
    for(int i = 0; i < 4; i++)
    {
      printf("%d, ", grid->cells[j]->neighbors[i]);
    }
    printf("\n");
  }
   fa_grid_free(grid);
  return 0;
}
