#include <iostream>
#include <graphics.h>
#include <stack>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <cstdio>

#define MAZE_ROWS 16
#define MAZE_COLS 21
#define CELL_SIZE 30

int mazeLayout[MAZE_ROWS][MAZE_COLS] =
{
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1},
};

int goalFound = 0;
int pathTaken[MAZE_ROWS][MAZE_COLS];

using namespace std;

void customDelay(int milliseconds)
{
    int end_time = clock() + milliseconds;
    while (clock() < end_time) {}
}

void renderMaze()
{
    for (int i = 0; i < MAZE_ROWS; i++)
    {
        for (int j = 0; j < MAZE_COLS; j++)
        {
            int xCoord = j * CELL_SIZE;
            int yCoord = i * CELL_SIZE;

            if (mazeLayout[i][j] == 1)
            {
                rectangle(xCoord, yCoord, xCoord + CELL_SIZE, yCoord + CELL_SIZE);
            }
            else if (mazeLayout[i][j] == 2)
            {
                circle(xCoord + CELL_SIZE / 2, yCoord + CELL_SIZE / 2, CELL_SIZE / 3);
            }
        }
    }
}

void drawPathOnMaze()
{
    for (int i = 0; i < MAZE_ROWS; i++)
    {
        for (int j = 0; j < MAZE_COLS; j++)
        {
            if (pathTaken[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, GREEN);
                bar(j * CELL_SIZE + CELL_SIZE / 6, i * CELL_SIZE + CELL_SIZE / 6,
                    (j + 1) * CELL_SIZE - CELL_SIZE / 6, (i + 1) * CELL_SIZE - CELL_SIZE / 6);
            }
        }
    }
}

void explorePaths(int row, int col)
{
    if (row < 0 || col < 0 || row >= MAZE_ROWS || col >= MAZE_COLS || goalFound || mazeLayout[row][col] == 1 || pathTaken[row][col] == 1)
    {
        return;
    }

    pathTaken[row][col] = 1;

    if (mazeLayout[row][col] == 2)
    {
        goalFound = 1;
        return;
    }

    explorePaths(row + 1, col);
    explorePaths(row, col + 1);
    explorePaths(row, col - 1);
    explorePaths(row - 1, col);

    if (!goalFound)
    {
        pathTaken[row][col] = 0;
    }

    customDelay(100);
    cleardevice();
    renderMaze();
    drawPathOnMaze();
}

int main()
{
    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    cleardevice();

    // Draw the "Solve Maze" button
    outtextxy(10, 50, "Hit the Button to solve the Maze");

    rectangle(10, 80, 275, 115);
    outtextxy(20, 90, "1. Solve Maze by Depth First Search");

    // Detect mouse clicks
    int x, y;
    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 10 && x <= 275 && y >= 20 && y <= 115)
            {
                explorePaths(0, 0); // Start maze solving
                break; // Exit the loop after solving the maze
            }
        }
    }

    if (goalFound)
    {
        //outtextxy(10, 440, "Path to reach the goal:");

        for (int i = 0; i < MAZE_ROWS; i++)
        {
            for (int j = 0; j < MAZE_COLS; j++)
            {
                if (pathTaken[i][j] == 1)
                {
                    char coordinates[50];
                    sprintf(coordinates, "-> [%d,%d] ", i, j);
                    outtextxy(10, 460 + (i * 20), coordinates);
                }
            }
        }
    }
    else
    {
        outtextxy(10, 440, "Path to the goal not found!");
    }

    getch();
    closegraph();
    return 0;
}
