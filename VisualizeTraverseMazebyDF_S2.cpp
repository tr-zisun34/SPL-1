#include <iostream>
#include <graphics.h>

#define ROWS 16
#define COLS 21

int maze[ROWS][COLS] = {
    // Your maze data
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

int found = 0;
int path[ROWS][COLS];

void drawMaze() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int x = j * 30;
            int y = i * 30;

            if (maze[i][j] == 1) {
                rectangle(x, y, x + 30, y + 30);
            } else if (maze[i][j] == 2) {
                circle(x + 15, y + 15, 10);
            }
        }
    }
}

void check(int i, int j) {
    if (i < 0 || j < 0 || i >= ROWS || j >= COLS || found || maze[i][j] == 1 || path[i][j] == 1) {
        return;
    }

    path[i][j] = 1;

    if (maze[i][j] == 2) {
        found = 1;
        return;
    }

    check(i + 1, j);
    check(i, j + 1);
    check(i, j - 1);
    check(i - 1, j);

    if (!found) {
        path[i][j] = 0;
    }
}

void drawPath() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (path[i][j] == 1) {
                setfillstyle(SOLID_FILL, GREEN);
                bar(j * 30 + 5, i * 30 + 5, (j + 1) * 30 - 5, (i + 1) * 30 - 5);
            }
        }
    }
}

int main() {
    int startI = 0;  // Starting row index
    int startJ = 0;  // Starting column index

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    cleardevice();

    drawMaze();

    check(startI, startJ);

    if (found) {
        std::cout << "Path to reach 2:\n";
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (path[i][j] == 1) std::cout << "-> [" << i << "," << j << "] ";
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "Path to 2 not found!\n";
    }

    if (found) {
        drawPath();
    }

    getch();
    closegraph();

    return 0;
}
