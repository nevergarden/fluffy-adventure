#include "cell.h"

#include <stdio.h>

int main()
{
    fa_cell_t * cell0 = fa_cell_init(0,0,0,NULL);
    fa_cell_t * cell1 = fa_cell_init(1,0,1,NULL);
    
    fa_cell_set_neighbor(cell0, EAST, cell1); // cell1 is at east of cell0
    fa_cell_link(cell0, cell1);
    
    fa_cell_free(cell0);
    fa_cell_free(cell1);
    return 0;
}