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

using namespace std;

void customDelay(int milliseconds) {
    int end_time = clock() + milliseconds;
    while (clock() < end_time) {}
}

void renderMaze() {
    for (int i = 0; i < MAZE_ROWS; i++) {
        for (int j = 0; j < MAZE_COLS; j++) {
            int xCoord = j * CELL_SIZE;
            int yCoord = i * CELL_SIZE;

            if (mazeLayout[i][j] == 1) {
                rectangle(xCoord, yCoord, xCoord + CELL_SIZE, yCoord + CELL_SIZE);
            } else if (mazeLayout[i][j] == 2) {
                circle(xCoord + CELL_SIZE / 2, yCoord + CELL_SIZE / 2, CELL_SIZE / 3);
            }
        }
    }
}

void drawPathOnMaze() {
    for (int i = 0; i < MAZE_ROWS; i++) {
        for (int j = 0; j < MAZE_COLS; j++) {
            if (pathTaken[i][j] == 1) {
                setfillstyle(SOLID_FILL, GREEN);
                bar(j * CELL_SIZE + CELL_SIZE / 6, i * CELL_SIZE + CELL_SIZE / 6,
                    (j + 1) * CELL_SIZE - CELL_SIZE / 6, (i + 1) * CELL_SIZE - CELL_SIZE / 6);
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

    customDelay(100);
    cleardevice();
    renderMaze();
    drawPathOnMaze();
}

int main() {
    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    cleardevice();
    renderMaze();

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    cleardevice();

    // Draw the name input field
    outtextxy(10, 400, "Enter Your Name: ");
    char name[50] = {0}; // Initialize the name array
    int nameX = 160;
    int nameY = 400;
    int ch;
    int i = 0;

    while (true) {
        ch = getch();

        if (ch == 13) { // Enter key
            name[i] = '\0';
            break;
        } else if (ch == 8) { // Backspace key
            if (i > 0) {
                i--;
                nameX -= textwidth(&name[i]);
                outtextxy(nameX, nameY, " ");
            }
        } else {
            name[i] = ch;
            outtextxy(nameX, nameY, &name[i]);
            nameX += textwidth(&name[i]);
            i++;
        }
    }

    // Display the entered name
    outtextxy(10, 420, "Hello, ");
    outtextxy(60, 420, name);

    // Draw the "Solve Maze" button
    rectangle(50, 350, 150, 380);
    outtextxy(60, 360, "Solve Maze");

    // Detect mouse clicks
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 50 && x <= 150 && y >= 350 && y <= 380) {
                // The user clicked the "Solve Maze" button
                explorePaths(0, 0); // Start maze solving
                break; // Exit the loop after solving the maze
            }
        }
    }

    if (goalFound) {
        outtextxy(10, 440, "Path to reach the goal:");

        for (int i = 0; i < MAZE_ROWS; i++) {
            for (int j = 0; j < MAZE_COLS; j++) {
                if (pathTaken[i][j] == 1) {
                    char coordinates[50];
                    sprintf(coordinates, "-> [%d,%d] ", i, j);
                    outtextxy(10, 460 + (i * 20), coordinates);
                }
            }
        }
    } else {
        outtextxy(10, 440, "Path to the goal not found!");
    }

    getch();
    closegraph();
    return 0;
}
