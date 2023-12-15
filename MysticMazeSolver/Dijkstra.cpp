#include <bits/stdc++.h>
#include <graphics.h>
#include <stack>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
#define MAZE_ROWS_of_Dij 16
#define MAZE_COLS_of_Dij 21
#define CELL_SIZE_of_Dij 30

int mazeLayoutOfDijkstra[MAZE_ROWS_of_Dij][MAZE_COLS_of_Dij] =
    {
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

int goalFoundOfDijkstra = 0;
int pathTakenOfDijkstra[MAZE_ROWS_of_Dij][MAZE_COLS_of_Dij];
int distanceOfDijkstra[MAZE_ROWS_of_Dij][MAZE_COLS_of_Dij];

// Function to render the maze
void renderMazeOfDijkstra()
{
    for (int i = 0; i < MAZE_ROWS_of_Dij; i++)
    {
        for (int j = 0; j < MAZE_COLS_of_Dij; j++)
        {
            int xCoord = j * CELL_SIZE_of_Dij;
            int yCoord = i * CELL_SIZE_of_Dij;

            if (mazeLayoutOfDijkstra[i][j] == 1)
            {
                rectangle(xCoord, yCoord, xCoord + CELL_SIZE_of_Dij, yCoord + CELL_SIZE_of_Dij);
            }
            else if (mazeLayoutOfDijkstra[i][j] == 2)
            {
                circle(xCoord + CELL_SIZE_of_Dij / 2, yCoord + CELL_SIZE_of_Dij / 2, CELL_SIZE_of_Dij / 3);
            }
        }
    }
}

void customDelayOfDijkstra(int milliseconds)
{
    int end_time = clock() + milliseconds;
    while (clock() < end_time) {}
}

void drawPathOnMazeOfDijkstra()
{
    for (int i = 0; i < MAZE_ROWS_of_Dij; i++)
    {
        for (int j = 0; j < MAZE_COLS_of_Dij; j++)
        {
            if (pathTakenOfDijkstra[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, CYAN);
                bar(j * CELL_SIZE_of_Dij + CELL_SIZE_of_Dij / 6, i * CELL_SIZE_of_Dij + CELL_SIZE_of_Dij / 6,
                    (j + 1) * CELL_SIZE_of_Dij - CELL_SIZE_of_Dij / 6, (i + 1) * CELL_SIZE_of_Dij - CELL_SIZE_of_Dij / 6);
            }
        }
    }
}

// Dijkstra's algorithm
void dijkstra_alg(int startX, int startY, int endX, int endY)
{
    const int INF = INT_MAX;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int i = 0; i < MAZE_ROWS_of_Dij; i++)
    {
        for (int j = 0; j < MAZE_COLS_of_Dij; j++)
        {
            ::distanceOfDijkstra[i][j] = INF;
            pathTakenOfDijkstra[i][j] = 0;
        }
    }

    ::distanceOfDijkstra[startX][startY] = 0;

    priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;
    pq.push({0, {startX, startY}});

    while (!pq.empty())
    {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        int dist = pq.top().first;
        pq.pop();

        pathTakenOfDijkstra[x][y] = 1;

        if (x == endX && y == endY)
        {
            goalFoundOfDijkstra = 1;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < MAZE_ROWS_of_Dij && ny >= 0 && ny < MAZE_COLS_of_Dij && !pathTakenOfDijkstra[nx][ny] && mazeLayoutOfDijkstra[nx][ny] != 1)
            {
                int newDist = ::distanceOfDijkstra[x][y] + 1;
                if (newDist < ::distanceOfDijkstra[nx][ny])
                {
                    ::distanceOfDijkstra[nx][ny] = newDist;
                    pq.push({newDist, {nx, ny}});
                    customDelayOfDijkstra(100);

                    cleardevice();
                    renderMazeOfDijkstra();
                    drawPathOnMazeOfDijkstra();
                }
            }
        }
    }
}

void Dijkstra()
{
    int startingRow = 0;
    int startingCol = 0;

    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    // Initially, display a black screen
    cleardevice();

    outtextxy(10, 50, "Hit the Button to solve the Maze");

    rectangle(10, 80, 275, 115);
    outtextxy(20, 90, "1. Solve Maze by Dijkstra's Algorithm");

    int x, y;

    //cout << "Enter Starting Row and Column: ";
    //cin >> startingRow;
    //cin >> startingCol;

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 10 && x <= 275 && y >= 20 && y <= 115)
            {
                goalFoundOfDijkstra = 0;
                cleardevice();
                renderMazeOfDijkstra();
                dijkstra_alg(startingRow, startingCol, 15, 15);

                if (goalFoundOfDijkstra)
                {
                    cout << "Path to reach the goal: " << endl;
                    for (int i = 0; i < MAZE_ROWS_of_Dij; i++)
                    {
                        for (int j = 0; j < MAZE_COLS_of_Dij; j++)
                        {
                            if (pathTakenOfDijkstra[i][j] == 1)
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
