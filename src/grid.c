#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "grid.h"
#include "cell.h"

Cell **create_grid(void)
{
    // start the pattern at any place on the grid

    int shift_x = rand() % (LENGTH - COLONY_LENGTH);
    int shift_y = rand() % (WIDTH - COLONY_WIDTH);

    //Lock memory for the grid
    Cell **grid = malloc(LENGTH * sizeof(Cell *));
    for (int i = 0; i < LENGTH; i++)
    {
        grid[i] = malloc(WIDTH * sizeof(Cell));
    }

    //Initialize the grid
    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            Cell new_cell;
            if (i>=shift_x && i<shift_x + COLONY_LENGTH && j>=shift_y && j<=shift_y+COLONY_WIDTH)
            {
                new_cell = create_cell(i, j, rand() % 2);
            }
            else 
            {
                new_cell = create_cell(i, j, 0); // Grid is initialized with dead cells
            }
            
            grid[i][j] = new_cell;
        }
    }

    return grid;
}

void display_grid(Cell **grid)
{
    // Print the grid in the shell

    for (int i = 0; i < WIDTH + 2; i++)
    {
        printf("-");
    }
    for (int i = 0; i < LENGTH; i++)
    {
        printf("\n");
        printf("%d| ", i);
        for (int j = 0; j < WIDTH; j++)
        {
            Cell c = grid[i][j];
            if (c.alive)
            {
                printf("\033[42m \033[0m");
            }
            else
            {
                printf(" ");
            }
        }
        printf(" |");
    }
    printf("\n");
    for (int i = 0; i < WIDTH + 2; i++)
    {
        printf("-");
    }
    printf("\n");
}

void update_grid(Cell **grid)
{
    // Update the current state of the grid to the next generation of cells

    Cell **new_grid = malloc(LENGTH * sizeof(Cell *));
    for (int i = 0; i < LENGTH; i++)
    {
        new_grid[i] = malloc(WIDTH * sizeof(Cell));
    }
    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            Cell new_cell = create_cell(i, j, survive(grid, grid[i][j]));
            new_grid[i][j] = new_cell;
        }
    }

    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            grid[i][j] = new_grid[i][j];
        }
    }
    // For each malloc there is one free
    for (int i = 0; i < LENGTH; i++)
    {
        free(new_grid[i]);
    }
    free(new_grid);
}

void update_gridv2(Cell **grid)
{
    // Update the current state of the grid to the next generation of cells.
    //(update only cell with a living neighbor, faster version)

    Cell **new_grid = malloc(LENGTH * sizeof(Cell *));
    for (int i = 0; i < LENGTH; i++)
    {
        new_grid[i] = malloc(WIDTH * sizeof(Cell));
        for (int j = 0; j < WIDTH; j++)
        {
            new_grid[i][j].alive = 0; // here we don't refresh all the grid so be sure it is properly initialized
        }
    }

    int moves[9][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}; // cell neighborhood
    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (grid[i][j].alive)
            {
                Cell new_cell = create_cell(i, j, survive(grid, grid[i][j]));
                new_grid[i][j] = new_cell;

                int r, c;
                for (int m = 0; m < 9; m++)
                {
                    r = i + moves[m][0];
                    c = j + moves[m][1];

                    if (r >= 0 && r < LENGTH && c >= 0 && c < WIDTH && !(grid[r][c].alive)) // only update dead one cause living one will be update
                    {
                        Cell new_cell = create_cell(r, c, survive(grid, grid[r][c]));
                        new_grid[r][c] = new_cell;
                    }
                }
            }
        }
    }

    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            grid[i][j] = new_grid[i][j];
        }
    }
    // For each malloc there is one free
    for (int i = 0; i < LENGTH; i++)
    {
        free(new_grid[i]);
    }
    free(new_grid);
}

void simulate(Cell **grid)
{
    // Simulate the evolution of the initial cells' configuration

    int days = 0;
    printf("Grid at day 0: \n");
    display_grid(grid);
   
    while (1)
    {
        days++;
        system("cls");
        printf("\n");
        printf("Grid at day %d: \n", days);
        // update_grid(grid);
        update_gridv2(grid);
        display_grid(grid);
    }
}