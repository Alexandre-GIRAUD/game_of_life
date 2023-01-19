#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "grid.h"

Cell create_cell(int x, int y, int alive)
{
    Cell c;
    c.x = x;
    c.y = y;
    c.alive = alive;
    return c;
}

void state_cell(Cell c)
{
    if (c.alive)
    {
        printf("This cell is alive at (%d,%d)", c.x, c.y);
    }
    else
    {
        printf("This cell is dead at (%d,%d)", c.x, c.y);
    }
}

int survive(Cell **grid, Cell c)
{
    int moves[9][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}, {0, 0}};
    int neighbors = 0;
    int i = 0;

    for (i = 0; i < 9; i++)
    {
        int neigh_row = c.x + moves[i][0];
        int neigh_col = c.y + moves[i][1];

        if (neigh_row >= 0 && neigh_row < LENGTH && neigh_col >= 0 && neigh_col < WIDTH && grid[neigh_row][neigh_col].alive == 1)
        {
            neighbors += 1;
        }
    }

    int survive= 0;
    if (grid[c.x][c.y].alive){
        if(neighbors==2 || neighbors==3) {
            survive = 1;
        }
    }
    else{
        if (neighbors==3){
            survive=1;
        }
    }
    return survive;
}
