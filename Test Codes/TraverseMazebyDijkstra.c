#include <stdio.h>
#include <limits.h>

#define ROWS 16
#define COLS 21

int maze[ROWS][COLS] = {
    // ... (same maze as before)
    {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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
    {1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1},
};

int distances[ROWS][COLS];
int parents[ROWS][COLS];

// Utility function to get the minimum distance cell
int minDistanceCell() {
    int minDist = INT_MAX;
    int minI = -1, minJ = -1;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (!parents[i][j] && distances[i][j] < minDist) {
                minDist = distances[i][j];
                minI = i;
                minJ = j;
            }
        }
    }

    return minI * COLS + minJ;
}

void printPath(int endI, int endJ) {
    if (endI >= 0 && endI < ROWS && endJ >= 0 && endJ < COLS) {
        if (parents[endI][endJ] != 0) {
            printPath(parents[endI][endJ] / COLS, parents[endI][endJ] % COLS);
            printf("-> [%d,%d] ", endI, endJ);
        } else {
            printf("[%d,%d] ", endI, endJ);
        }
    }
}

void dijkstra(int startI, int startJ) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            distances[i][j] = INT_MAX;
            parents[i][j] = 0;
        }
    }

    distances[startI][startJ] = 0;

    for (int count = 0; count < ROWS * COLS; count++) {
        int cellIndex = minDistanceCell();
        int i = cellIndex / COLS;
        int j = cellIndex % COLS;

        parents[i][j] = 1;

        // Check neighboring cells
       if (maze[i][j] == 2) {
            printf("Shortest distance to reach 2: %d\n", distances[i][j]);
            printf("Path to reach 2:\n");
            printPath(i, j);
            printf("\n");
            return;
        }

        // Update distances of neighboring cells
        int neighbors[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int k = 0; k < 4; k++) {
            int ni = i + neighbors[k][0];
            int nj = j + neighbors[k][1];

            if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS &&
                !parents[ni][nj] && maze[ni][nj] != 1 &&
                distances[i][j] + maze[ni][nj] < distances[ni][nj]) {
                distances[ni][nj] = distances[i][j] + maze[ni][nj];
            }
        }
    }

    printf("No valid path to 2 found.\n");
}

int main() {
    int startI = 1;  // Starting row index
    int startJ = 1;  // Starting column index

    dijkstra(startI, startJ);

    return 0;
}
