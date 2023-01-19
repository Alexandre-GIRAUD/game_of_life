#ifndef H_CELL
#define H_CELL

// enum State {Dead,Alive};

typedef struct Cell Cell;
struct Cell
{
    int x;
    int y;
    int alive;
};

Cell create_cell(int x, int y, int alive); // create a new cell
void state_cell(Cell c);                   // print the state of the cell
int survive(Cell **grid, Cell c);          // return 1 if the cell is alive at the next step, 0 otherwise.

#endif