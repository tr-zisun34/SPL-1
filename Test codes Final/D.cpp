#include <iostream>
#include <graphics.h>
#include <stack>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <cstdio>
#include <limits.h>

#define MAZE_ROWS 16
#define MAZE_COLS 21
#define CELL_SIZE 30

int mazeLayout[MAZE_ROWS][MAZE_COLS] = {
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
};

int goalFound = 0;
int pathTaken[MAZE_ROWS][MAZE_COLS];
int distance[MAZE_ROWS][MAZE_COLS];

using namespace std;

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

void customDelay(int milliseconds)
{
    int end_time = clock() + milliseconds;
    while (clock() < end_time) {}
}

void drawPathOnMaze()
{
    for (int i = 0; i < MAZE_ROWS; i++)
    {
        for (int j = 0; j < MAZE_COLS; j++)
        {
            if (pathTaken[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, CYAN);
                bar(j * CELL_SIZE + CELL_SIZE / 6, i * CELL_SIZE + CELL_SIZE / 6,
                    (j + 1) * CELL_SIZE - CELL_SIZE / 6, (i + 1) * CELL_SIZE - CELL_SIZE / 6);
            }
        }
    }
}

void dijkstra(int startX, int startY, int endX, int endY)
{
    const int INF = INT_MAX;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int i = 0; i < MAZE_ROWS; i++)
    {
        for (int j = 0; j < MAZE_COLS; j++)
        {
            ::distance[i][j] = INF;  // Use :: to specify the global namespace
            pathTaken[i][j] = 0;
        }
    }

    ::distance[startX][startY] = 0;  // Use :: to specify the global namespace

    for (int k = 0; k < MAZE_ROWS * MAZE_COLS; k++)
    {
        int minDist = INF;
        int x = -1, y = -1;

        for (int i = 0; i < MAZE_ROWS; i++)
        {
            for (int j = 0; j < MAZE_COLS; j++)
            {
                if (!pathTaken[i][j] && ::distance[i][j] < minDist)  // Use :: to specify the global namespace
                {
                    minDist = ::distance[i][j];  // Use :: to specify the global namespace
                    x = i;
                    y = j;
                }
            }
        }

        if (x == -1 || y == -1)
            break;

        pathTaken[x][y] = 1;

        if (x == endX && y == endY)
            return;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < MAZE_ROWS && ny >= 0 && ny < MAZE_COLS && !pathTaken[nx][ny] && mazeLayout[nx][ny] != 1)
            {
                int newDist = ::distance[x][y] + 1;  // Use :: to specify the global namespace
                if (newDist < ::distance[nx][ny])  // Use :: to specify the global namespace
                {
                    ::distance[nx][ny] = newDist;  // Use :: to specify the global namespace
                    customDelay(100);

                    cleardevice();
                    renderMaze();
                    drawPathOnMaze();
                }
            }
        }
    }
}


int main()
{
    int startingRow = 0;
    int startingCol = 0;

    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    cleardevice();
    renderMaze();
    drawPathOnMaze();

    dijkstra(startingRow, startingCol, 15, 16);

    getch();
    closegraph();

    return 0;
}
