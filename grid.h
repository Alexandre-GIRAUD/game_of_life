#ifndef H_GRID
#define H_GRID
#define WIDTH 100
#define LENGTH 50
#include "cell.h"

Cell **create_grid(char set[][18], int rows_set, int cols_set); // create a new grid from map
void display_grid(Cell **grid);                                 // print the grid in the shell
Cell **update_grid(Cell **grid);                                // run one step of evolution
void simulate(Cell **grid);

#endif