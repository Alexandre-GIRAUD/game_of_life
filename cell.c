#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "grid.h"

Cell create_cell(int x, int y, int alive)
{
    Cell c;
    c.x = x; //row position on the grid
    c.y = y; //col position on the grid
    c.alive = alive; //bool wheter a cell is alive (1) or dead (0)
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
    //Regarding the neighborhood of the cell, return True if the cell survive to till the next generation. False otherwise.

    int moves[9][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}, {0, 0}}; //cell neighborhood
    int neighbors = 0;
    
    for (int i = 0; i < 9; i++)
    {
        int neigh_row = c.x + moves[i][0];
        int neigh_col = c.y + moves[i][1];
        
        if (neigh_row >= 0 && neigh_row < LENGTH && neigh_col >= 0 && neigh_col < WIDTH && grid[neigh_row][neigh_col].alive)
        {
            neighbors += 1;
        }
    }

    int survive= 0;

    if (c.alive==1){
        if(neighbors==3 || neighbors==4) {//a cell will survive if she is alive and has 3 or 4 neighbors
            survive = 1;
        }
    }
    else{
        
        if (neighbors==3){ //or is dead and has exactly three neighbors
            survive=1;
        }
    }
    return survive;
}
