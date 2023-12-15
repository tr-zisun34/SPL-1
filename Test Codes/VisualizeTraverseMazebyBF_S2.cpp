#include <iostream>
#include <graphics.h>
#include <queue>

#define MAZE_ROWS 16
#define MAZE_COLS 21

int mazeLayout[MAZE_ROWS][MAZE_COLS] = {
    // ... (array values represent the maze structure)
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
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
    {1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1},
};

int goalFound = 0;
int pathTaken[MAZE_ROWS][MAZE_COLS];
int parentRow[MAZE_ROWS][MAZE_COLS];
int parentCol[MAZE_ROWS][MAZE_COLS];

void renderMaze() {
    for (int i = 0; i < MAZE_ROWS; i++) {
        for (int j = 0; j < MAZE_COLS; j++) {
            int xCoord = j * 30;
            int yCoord = i * 30;

            if (mazeLayout[i][j] == 1) {
                rectangle(xCoord, yCoord, xCoord + 30, yCoord + 30);
            } else if (mazeLayout[i][j] == 2) {
                circle(xCoord + 15, yCoord + 15, 10);
            }
        }
    }
}

void bfs(int startRow, int startCol) {
    std::queue<std::pair<int, int> > q;
    q.push(std::make_pair(startRow, startCol));

    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if (row < 0 || col < 0 || row >= MAZE_ROWS || col >= MAZE_COLS || mazeLayout[row][col] == 1 || pathTaken[row][col] == 1) {
            continue;
        }

        pathTaken[row][col] = 1;

        if (mazeLayout[row][col] == 2) {
            goalFound = 1;
            return;
        }

        q.push(std::make_pair(row + 1, col));
        q.push(std::make_pair(row, col + 1));
        q.push(std::make_pair(row, col - 1));
        q.push(std::make_pair(row - 1, col));


        parentRow[row + 1][col] = row;
        parentCol[row + 1][col] = col;
        parentRow[row][col + 1] = row;
        parentCol[row][col + 1] = col;
        parentRow[row][col - 1] = row;
        parentCol[row][col - 1] = col;
        parentRow[row - 1][col] = row;
        parentCol[row - 1][col] = col;
    }
}

void drawPathOnMaze() {
    for (int i = 0; i < MAZE_ROWS; i++) {
        for (int j = 0; j < MAZE_COLS; j++) {
            if (pathTaken[i][j] == 1) {
                setfillstyle(SOLID_FILL, GREEN);
                bar(j * 30 + 5, i * 30 + 5, (j + 1) * 30 - 5, (i + 1) * 30 - 5);
            }
        }
    }
}

int main() {
    int startingRow = 0;
    int startingCol = 0;

    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    cleardevice();

    renderMaze();

    bfs(startingRow, startingCol);

    if (goalFound) {
        std::cout << "Path to reach the goal:\n";
        int row = MAZE_ROWS - 1;
        int col = MAZE_COLS - 1;
        while (row != startingRow || col != startingCol) {
            pathTaken[row][col] = 1;
            int newRow = parentRow[row][col];
            int newCol = parentCol[row][col];
            row = newRow;
            col = newCol;
        }
    } else {
        std::cout << "Path to the goal not found!\n";
    }

    if (goalFound) {
        drawPathOnMaze();
    }

    getch();
    closegraph();

    return 0;
}
