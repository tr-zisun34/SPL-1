#include <bits/stdc++.h>
#include <graphics.h>
#include <stack>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

#define MAZE_ROWS 16
#define MAZE_COLS 21
#define CELL_SIZE 30

int mazeLayout[MAZE_ROWS][MAZE_COLS] =
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

int goalFound = 0;
int pathTaken[MAZE_ROWS][MAZE_COLS];
int distance[MAZE_ROWS][MAZE_COLS];

// Function to render the maze
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

// Heuristic function for A* algorithm
int calculateHeuristic(int x, int y, int endX, int endY)
{
    // Euclidean distance heuristic
    return static_cast<int>(sqrt((x - endX) * (x - endX) + (y - endY) * (y - endY)));
}

void aStar(int startX, int startY, int endX, int endY)
{
    const int INF = INT_MAX;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int i = 0; i < MAZE_ROWS; i++)
    {
        for (int j = 0; j < MAZE_COLS; j++)
        {
            ::distance[i][j] = INF;
            pathTaken[i][j] = 0;
        }
    }

    ::distance[startX][startY] = 0;

    priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;
    pq.push({calculateHeuristic(startX, startY, endX, endY), {startX, startY}});

    while (!pq.empty())
    {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        pathTaken[x][y] = 1;

        if (x == endX && y == endY)
        {
            goalFound = 1;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < MAZE_ROWS && ny >= 0 && ny < MAZE_COLS && !pathTaken[nx][ny] && mazeLayout[nx][ny] != 1)
            {
                int newDist = ::distance[x][y] + 1;
                if (newDist < ::distance[nx][ny])
                {
                    ::distance[nx][ny] = newDist;
                    pq.push({newDist + calculateHeuristic(nx, ny, endX, endY), {nx, ny}});
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

    // Initially, display a black screen
    cleardevice();

    outtextxy(10, 50, "Hit the Button to solve the Maze");

    rectangle(10, 80, 275, 115);
    outtextxy(20, 90, "1. Solve Maze by A* Algorithm");

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
                goalFound = 0;
                cleardevice();
                renderMaze();
                aStar(startingRow, startingCol, 15, 15);

                if (goalFound)
                {
                    cout << "Path to reach the goal: " << endl;
                    for (int i = 0; i < MAZE_ROWS; i++)
                    {
                        for (int j = 0; j < MAZE_COLS; j++)
                        {
                            if (pathTaken[i][j] == 1)
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

    return 0;
}
