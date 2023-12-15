#include <iostream>
#include <graphics.h>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <cstdio>

#define MAZE_ROWSofBFS 16
#define MAZE_COLSofBFS 21
#define CELL_SIZEofBFS 30

int mazeDataofBFS[MAZE_ROWSofBFS][MAZE_COLSofBFS] =
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

int foundGoalofBFS = 0;
int pathFoundOfBFS[MAZE_ROWSofBFS][MAZE_COLSofBFS];

using namespace std;

struct MazePosition
{
    int x, y;

    MazePosition() : x(0), y(0) {}

    MazePosition(int _x, int _y) : x(_x), y(_y) {}
};

MazePosition mazeStack[MAZE_ROWSofBFS * MAZE_COLSofBFS];
int topIndex = -1;

void pushStack(MazePosition p)
{
    mazeStack[++topIndex] = p;
}

void popStack()
{
    --topIndex;
}

MazePosition peekStack()
{
    return mazeStack[topIndex];
}

bool isStackEmpty()
{
    return topIndex == -1;
}

void drawMazeOfBFS()
{
    for (int i = 0; i < MAZE_ROWSofBFS; i++)
    {
        for (int j = 0; j < MAZE_COLSofBFS; j++)
        {
            int xCoord = j * CELL_SIZEofBFS;
            int yCoord = i * CELL_SIZEofBFS;

            if (mazeDataofBFS[i][j] == 1)
            {
                rectangle(xCoord, yCoord, xCoord + CELL_SIZEofBFS, yCoord + CELL_SIZEofBFS);
            }
            else if (mazeDataofBFS[i][j] == 2)
            {
                circle(xCoord + CELL_SIZEofBFS / 2, yCoord + CELL_SIZEofBFS / 2, CELL_SIZEofBFS / 3);
            }
        }
    }
}

void customWaitOfBFS(int milliseconds)
{
    int endTime = clock() + milliseconds;
    while (clock() < endTime) {}
}

void drawPathOnMazeByBFS()
{
    for (int i = 0; i < MAZE_ROWSofBFS; i++)
    {
        for (int j = 0; j < MAZE_COLSofBFS; j++)
        {
            if (pathFoundOfBFS[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, CYAN);
                bar(j * CELL_SIZEofBFS + CELL_SIZEofBFS / 6, i * CELL_SIZEofBFS + CELL_SIZEofBFS / 6,
                    (j + 1) * CELL_SIZEofBFS - CELL_SIZEofBFS / 6, (i + 1) * CELL_SIZEofBFS - CELL_SIZEofBFS / 6);
            }
        }
    }
}

void findPathByBFS(int row, int col)
{
    pushStack(MazePosition(row, col));

    while (!isStackEmpty() && !foundGoalofBFS)
    {
        MazePosition current = peekStack();
        int x = current.x;
        int y = current.y;
        popStack();

        if (x < 0 || y < 0 || x >= MAZE_ROWSofBFS || y >= MAZE_COLSofBFS || mazeDataofBFS[x][y] == 1 || pathFoundOfBFS[x][y] == 1)
        {
            continue;
        }

        pathFoundOfBFS[x][y] = 1;

        if (mazeDataofBFS[x][y] == 2)
        {
            foundGoalofBFS = 1;
            break;
        }

        pushStack(MazePosition(x + 1, y));
        pushStack(MazePosition(x, y + 1));
        pushStack(MazePosition(x, y - 1));
        pushStack(MazePosition(x - 1, y));

        customWaitOfBFS(100);

        cleardevice();
        drawMazeOfBFS();
        drawPathOnMazeByBFS();
    }
}

void BFS()
{
    int startRow;
    int startCol;

    int k=0;

    for (int i=0; i<MAZE_COLSofBFS; i++){
        if(mazeDataofBFS[k][i]==0){
            startRow = i;
            startCol = k;
        }
    }

    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    cleardevice();

    outtextxy(10, 50, "Hit the Button to solve the Maze");

    rectangle(10, 80, 275, 115);
    outtextxy(20, 90, "1. Solve Maze by Breadth First Search");

    int x, y;

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 10 && x <= 275 && y >= 20 && y <= 115)
            {
                foundGoalofBFS = 0;
                cleardevice();
                drawMazeOfBFS();
                findPathByBFS(startRow, startCol);

                if (foundGoalofBFS)
                {
                    cout << "Path to reach the goal: " << endl;
                    for (int i = 0; i < MAZE_ROWSofBFS; i++)
                    {
                        for (int j = 0; j < MAZE_COLSofBFS; j++)
                        {
                            if (pathFoundOfBFS[i][j] == 1)
                            {
                                cout << "-> [" << i << "," << j << "] ";
                            }
                        }
                    }
                }
                else
                {
                    cout << "Path to the goal not found!";
                }
            }
        }
    }

    getch();
    closegraph();
}

