#include <iostream>
#include <graphics.h>

#define MAZE_ROWS 16
#define MAZE_COLS 21

int mazeLayout[MAZE_ROWS][MAZE_COLS] = {
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

void explorePaths(int row, int col) {
    if (row < 0 || col < 0 || row >= MAZE_ROWS || col >= MAZE_COLS || goalFound || mazeLayout[row][col] == 1 || pathTaken[row][col] == 1) {
        return;
    }

    pathTaken[row][col] = 1;

    if (mazeLayout[row][col] == 2) {
        goalFound = 1;
        return;
    }

    explorePaths(row + 1, col);
    explorePaths(row, col + 1);
    explorePaths(row, col - 1);
    explorePaths(row - 1, col);

    if (!goalFound) {
        pathTaken[row][col] = 0;
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

    explorePaths(startingRow, startingCol);

    if (goalFound) {
        std::cout << "Path to reach the goal:\n";
        for (int i = 0; i < MAZE_ROWS; i++) {
            for (int j = 0; j < MAZE_COLS; j++) {
                if (pathTaken[i][j] == 1) std::cout << "-> [" << i << "," << j << "] ";
            }
            std::cout << "\n";
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
