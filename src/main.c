#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "grid.h"

int main()
{
    printf("-------------------------\nWelcome to Game Of Life\n(-------------------------\n");

    /*
    // Initial state of the simulation
    int input_row = 20, input_col = 20;
    int input[input_row][input_col];
    for (int i = 0; i < input_row; i++)
    {
        for (int j = 0; j < input_col; j++)
        {
            input[i][j] = rand() % 2;
        }
    }
    */
    // Grid (LENGTH*WIDTH) creation and set is randomly placed
    Cell **grid = create_grid();

    // run simulation
    simulate(grid);

    // free grid space
    for (int i = 0; i < LENGTH; i++)
        free(grid[i]);

    free(grid);

    return 0;
}