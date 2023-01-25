#ifndef H_GRID
#define H_GRID
#define WIDTH 100
#define LENGTH 50
#define COLONY_LENGTH 20
#define COLONY_WIDTH 20
#include "cell.h"

Cell **create_grid(void);       // create a new grid from map
void display_grid(Cell **grid); // print the grid in the shell
void update_grid(Cell **grid);  // run one step of evolution
void update_gridv2(Cell **grid);
void simulate(Cell **grid);

#endif