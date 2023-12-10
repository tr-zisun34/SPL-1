#include <stdio.h>
#include <limits.h>

#define ROWS 15
#define COLS 21

int maze[21][15] =
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


int dist[ROWS][COLS];

void dijkstra(int startX, int startY, int goalX, int goalY) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            dist[i][j] = INT_MAX;
        }
    }

    dist[startX][startY] = 0;

    while (1) {
        int minDist = INT_MAX, u, v;

        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (dist[i][j] < minDist) {
                    minDist = dist[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        if (u == goalX && v == goalY) {
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = u + dx[i];
            int ny = v + dy[i];

            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && maze[nx][ny] != 1) {
                int newDist = dist[u][v] + 1;

                if (newDist < dist[nx][ny]) {
                    dist[nx][ny] = newDist;
                }
            }
        }

        dist[u][v] = INT_MAX;
    }
}

void printMaze() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int startX = 0;
    int startY = 0;
    int goalX, goalY;

    // Find the coordinates of the goal
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (maze[i][j] == 2) {
                goalX = i;
                goalY = j;
                break;
            }
        }
    }

    dijkstra(startX, startY, goalX, goalY);

    // Visualize the path
    printf("Shortest Path:\n");
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (maze[i][j] == 1) {
                printf("# ");
            } else if (maze[i][j] == 2) {
                printf("G ");
            } else if (dist[i][j] == INT_MAX) {
                printf("  ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
