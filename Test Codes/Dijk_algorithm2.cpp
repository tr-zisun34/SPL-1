#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>

#define ROWS 16
#define COLS 21

const int INF = 32767;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

struct Node {
    int x, y, dist;
};

struct NodePriorityQueue {
    struct Node *nodes;
    int size;
};

void push(struct NodePriorityQueue *pq, struct Node node) {
    pq->size++;
    pq->nodes = (struct Node *)realloc(pq->nodes, pq->size * sizeof(struct Node));
    pq->nodes[pq->size - 1] = node;
    int i = pq->size - 1;
    while (i > 0 && pq->nodes[i].dist < pq->nodes[(i - 1) / 2].dist) {
        struct Node temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        pq->nodes[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

struct Node pop(struct NodePriorityQueue *pq) {
    struct Node minNode = pq->nodes[0];
    pq->nodes[0] = pq->nodes[pq->size - 1];
    pq->size--;
    pq->nodes = (struct Node *)realloc(pq->nodes, pq->size * sizeof(struct Node));
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < pq->size && pq->nodes[left].dist < pq->nodes[i].dist) {
            smallest = left;
        }
        if (right < pq->size && pq->nodes[right].dist < pq->nodes[smallest].dist) {
            smallest = right;
        }
        if (smallest != i) {
            struct Node temp = pq->nodes[i];
            pq->nodes[i] = pq->nodes[smallest];
            pq->nodes[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return minNode;
}

void drawMazeStepByStep(int maze[ROWS][COLS], int path[ROWS][COLS], int currentX, int currentY) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 1) {
                setfillstyle(SOLID_FILL, RED);
                bar(j * 30, i * 30, (j + 1) * 30, (i + 1) * 30);
            } else if (maze[i][j] == 2) {
                setfillstyle(SOLID_FILL, GREEN);
                bar(j * 30, i * 30, (j + 1) * 30, (i + 1) * 30);
            } else if (path[i][j] == 1) {  // Highlight the shortest path cells
                setfillstyle(SOLID_FILL, YELLOW);  // You can choose a different color
                bar(j * 30, i * 30, (j + 1) * 30, (i + 1) * 30);
            }
        }
    }

    // Highlight the current cell
    setfillstyle(SOLID_FILL, BLUE);
    bar(currentY * 30, currentX * 30, (currentY + 1) * 30, (currentX + 1) * 30);

    delay(10); // Pause for a moment before the next step

    closegraph();
}



int dijkstraStepByStep(int maze[ROWS][COLS], int startX, int startY, int endX, int endY, int path[ROWS][COLS]) {
    int distance[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            distance[i][j] = INF;
            path[i][j] = 0;  // Initialize the path array
        }
    }

    struct NodePriorityQueue pq;
    pq.size = 0;
    pq.nodes = NULL;

    struct Node startNode = {startX, startY, 0};
    push(&pq, startNode);
    distance[startX][startY] = 0;

    while (pq.size > 0) {
        struct Node current = pop(&pq);

        if (current.x == endX && current.y == endY) {
            // Reconstruct the shortest path
            int x = endX, y = endY;
            while (x != startX || y != startY) {
                path[x][y] = 1;  // Mark the path
                int prevDist = distance[x][y] - 1;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && distance[nx][ny] == prevDist) {
                        x = nx;
                        y = ny;
                        break;
                    }
                }
            }
            path[startX][startY] = 1;  // Mark the start point
            return distance[endX][endY];
        }

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && maze[nx][ny] != 1) {
                int newDist = current.dist + 1;
                if (newDist < distance[nx][ny]) {
                    distance[nx][ny] = newDist;
                    struct Node newNode = {nx, ny, newDist};
                    push(&pq, newNode);

                    // Call the drawMazeStepByStep function to show the current state
                    drawMazeStepByStep(maze, path, nx, ny);
                }
            }
        }
    }

    return -1; // No path found
}



int main() {
    int maze[ROWS][COLS] = {
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
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1}
    };

       int startX = 0;
    int startY = 0;

    int endX = -1;
    int endY = -1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 2) {
                endX = i;
                endY = j;
                break;
            }
        }
    }

    if (endX == -1 || endY == -1) {
        printf("Destination not found in the maze!\n");
        return 0;
    }

    int path[ROWS][COLS];  // Create a path array to store the shortest path
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            path[i][j] = 0;
        }
    }

    int shortestPathLength = dijkstraStepByStep(maze, startX, startY, endX, endY, path);

    if (shortestPathLength != -1) {
        printf("Shortest path length: %d\n", shortestPathLength);
    } else {
        printf("No path found!\n");
        return 0;
    }

    return 0;
}
