#include <iostream>
#include <graphics.h>
#include <stack>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <cstdio>

#define MAZE_ROWS_of_DFS 16
#define MAZE_COLS_of_DFS 21
#define CELL_SIZE_of_DFS 30

int mazeLayoutOfDFS[MAZE_ROWS_of_DFS][MAZE_COLS_of_DFS] =
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

int goalFoundOfDFS = 0;
int pathTakenbyDFS[MAZE_ROWS_of_DFS][MAZE_COLS_of_DFS];

using namespace std;

// Function to render the maze
void renderMazeByDFS()
{
    for (int i = 0; i < MAZE_ROWS_of_DFS; i++)
    {
        for (int j = 0; j < MAZE_COLS_of_DFS; j++)
        {
            int xCoord = j * CELL_SIZE_of_DFS;
            int yCoord = i * CELL_SIZE_of_DFS;

            if (mazeLayoutOfDFS[i][j] == 1)
            {
                rectangle(xCoord, yCoord, xCoord + CELL_SIZE_of_DFS, yCoord + CELL_SIZE_of_DFS);
            }
            else if (mazeLayoutOfDFS[i][j] == 2)
            {
                circle(xCoord + CELL_SIZE_of_DFS / 2, yCoord + CELL_SIZE_of_DFS / 2, CELL_SIZE_of_DFS / 3);
            }
        }
    }
}

void custom_Delay_DFS(int milliseconds)
{
    int end_time = clock() + milliseconds;
    while (clock() < end_time) {}
}

void drawPath_OnMaze_DFS()
{
    for (int i = 0; i < MAZE_ROWS_of_DFS; i++)
    {
        for (int j = 0; j < MAZE_COLS_of_DFS; j++)
        {
            if (pathTakenbyDFS[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, CYAN);
                bar(j * CELL_SIZE_of_DFS + CELL_SIZE_of_DFS / 6, i * CELL_SIZE_of_DFS + CELL_SIZE_of_DFS / 6,
                    (j + 1) * CELL_SIZE_of_DFS - CELL_SIZE_of_DFS / 6, (i + 1) * CELL_SIZE_of_DFS - CELL_SIZE_of_DFS / 6);
            }
        }
    }
}

void explore_Paths_DFS(int row, int col)
{
    if (row < 0 || col < 0 || row >= MAZE_ROWS_of_DFS || col >= MAZE_COLS_of_DFS || goalFoundOfDFS || mazeLayoutOfDFS[row][col] == 1 || pathTakenbyDFS[row][col] == 1)
    {
        return;
    }

    pathTakenbyDFS[row][col] = 1;

    if (mazeLayoutOfDFS[row][col] == 2)
    {
        goalFoundOfDFS = 1;
        return;
    }

    explore_Paths_DFS(row + 1, col);
    explore_Paths_DFS(row, col + 1);
    explore_Paths_DFS(row, col - 1);
    explore_Paths_DFS(row - 1, col);

    if (!goalFoundOfDFS)
    {
        pathTakenbyDFS[row][col] = 0;
    }

    custom_Delay_DFS(100);

    cleardevice();
    renderMazeByDFS();
    drawPath_OnMaze_DFS();
}

void DFS()
{
    int startingRow ;
    int startingCol ;

    int k=0;

    for (int i=0; i<MAZE_COLS_of_DFS; i++){
        if(mazeLayoutOfDFS[k][i]==0){
            startingRow = i;
            startingCol = k;
        }
    }
    cout << startingCol << endl << startingRow;

    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    // Initially, display a black screen
    cleardevice();

    outtextxy(10, 50, "Hit the Button to solve the Maze");

    rectangle(10, 80, 275, 115);
    outtextxy(20, 90, "1. Solve Maze by Depth First Search");

    int x, y;

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 10 && x <= 275 && y >= 20 && y <= 115)
            {
                goalFoundOfDFS = 0;
                cleardevice();
                renderMazeByDFS();
                explore_Paths_DFS(startingRow, startingCol);

                if (goalFoundOfDFS)
                {
                    cout << "Path to reach the goal: " << endl;
                    for (int i = 0; i < MAZE_ROWS_of_DFS; i++)
                    {
                        for (int j = 0; j < MAZE_COLS_of_DFS; j++)
                        {
                            if (pathTakenbyDFS[i][j] == 1)
                            {
                                cout << "-> [" << i << "," << j << "] ";
                            }
                        }
                    }
                }
                else
                {
                    cout << "Path to the goal not found!" ;
                }
            }
        }
    }

    getch();
    closegraph();

}
