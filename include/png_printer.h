#ifndef FLUFFY_ADV_PNG_PRINTER_H
#define FLUFFY_ADV_PNG_PRINTER_H

#include <stdint.h>
#include <math.h>
#include "grid.h"
#include "libattopng.h"

#define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))

void libattopng_lineto(libattopng_t * png, int x0, int y0, int x1, int y1, uint32_t color)
{
    printf("(%d,%d)->(%d,%d)\n", x0,y0,y0,y1);
    int dx = abs(x1-x0); int sx = (x0 < x1) ? 1 : -1;
    int dy = -1*abs(y1-y0); int sy = (y0 < y1) ? 1 : -1;
    int err = dx+dy;
    int e2;

    while (true)
    {
        libattopng_set_pixel(png, x0, y0, color);
        if(x0==x1 && y0 == y1) break;
        e2 = 2*err;
        if(e2 >= dy) { err += dy; x0 += sx; }
        if(e2 <= dx) { err += dx; y0 += sy; }
    }
}

void libattopng_fill(libattopng_t * png, uint32_t color) {
    for (size_t i = 0; i < png->width; i++)
        for (size_t j = 0; j < png->height; j++)
            libattopng_set_pixel(png, i, j, color);
}

void fa_grid_to_png(fa_grid_t * grid, size_t cell_size, char * filename) {
    size_t img_width = cell_size * grid->column_count;
    size_t img_height = cell_size * grid->row_count;

    uint32_t background_color = RGBA(255,255,255,255);
    uint32_t wall_color = RGBA(0,0,0,255);
    
    libattopng_t* png = libattopng_new(img_width+1, img_height+1, PNG_RGB);

    libattopng_fill(png, background_color);

    for (size_t row = 0; row < grid->row_count; row++)
    {
        for (size_t column = 0; column < grid->column_count; column++)
        {
            fa_cell_t * cell = fa_grid_get_cell(grid, row, column);
            int x1 = column * cell_size;
            int y1 = row * cell_size;
            int x2 = (column+1) * cell_size;
            int y2 = (row+1) * cell_size;

            if(cell->neighbors[0] == -1)
                libattopng_lineto(png, x1, y1, x2, y1, wall_color);
            if(cell->neighbors[3] == -1)
                libattopng_lineto(png, x1, y1, x1, y2, wall_color);
            
            if(!fa_cell_has_east_link(cell))
                libattopng_lineto(png, x2, y1, x2, y2, wall_color);
            if(!fa_cell_has_south_link(cell))
                libattopng_lineto(png, x1, y2, x2, y2, wall_color);
        }
    }

    libattopng_save(png, filename);
    libattopng_destroy(png);
}

#endif