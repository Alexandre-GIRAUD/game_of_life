#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "grid.h"
#include "cell.h"

Cell **create_grid(char set[][18], int rows_set, int cols_set)
{

    // start the pattern at any place on the grid
    int shift_x = rand() % (WIDTH - cols_set);
    int shift_y = rand() % (LENGTH - rows_set);
    Cell **grid = malloc(LENGTH * sizeof(Cell *));
    for (int i = 0; i < LENGTH; i++)
        grid[i] = malloc(WIDTH * sizeof(Cell));
    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            Cell new_cell = create_cell(i, j, 0);
            grid[i][j] = new_cell;
        }
    }

    for (int i = 0; i < rows_set; i++)
    {
        for (int j = 0; j < cols_set; j++)
        {
            Cell new_cell = create_cell(i, j, set[i][j]);
            grid[i + shift_x][j + shift_y] = new_cell;
        }
    }
    return grid;
}

void display_grid(Cell **grid)
{
    for (int i = 0; i < WIDTH + 2; i++)
    {
        printf("-");
    }
    for (int i = 0; i < LENGTH; i++)
    {
        printf("\n");
        printf("| ");
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

Cell **update_grid(Cell **grid)
{
    Cell **new_grid = malloc(LENGTH * sizeof(Cell *));
    for (int i = 0; i < LENGTH; i++)
        new_grid[i] = malloc(WIDTH * sizeof(Cell));

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

void simulate(Cell **grid)
{
    int days = 0;
    printf("Grid at day 0: \n");
    display_grid(grid);
    while (1)
    {
        system("cls");
        printf("\n");
        update_grid(grid);
        display_grid(grid);
    }
}