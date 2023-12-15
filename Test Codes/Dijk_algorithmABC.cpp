#include <iostream>
#include <graphics.h>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

#define MAZE_ROWS 16
#define MAZE_COLS 21
#define CELL_SIZE 30
#define INF 32767

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

// Function to render the maze
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

void customDelay(int milliseconds) {
    int end_time = clock() + milliseconds;
    while (clock() < end_time) {}
}

void drawPathOnMaze() {
    for (int i = 0; i < MAZE_ROWS; i++) {
        for (int j = 0; j < MAZE_COLS; j++) {
            if (pathTaken[i][j] == 1) {
                setfillstyle(SOLID_FILL, CYAN);
                bar(j * CELL_SIZE + CELL_SIZE / 6, i * CELL_SIZE + CELL_SIZE / 6,
                    (j + 1) * CELL_SIZE - CELL_SIZE / 6, (i + 1) * CELL_SIZE - CELL_SIZE / 6);
            }
        }
    }
}

struct Node {
    int x, y, dist;

    Node(int _x, int _y, int _dist) : x(_x), y(_y), dist(_dist) {}
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        return a.dist > b.dist;
    }
};

int dijkstra(int startX, int startY, int endX, int endY) {
    int distance[MAZE_ROWS][MAZE_COLS];
    for (int i = 0; i < MAZE_ROWS; i++) {
        for (int j = 0; j < MAZE_COLS; j++) {
            distance[i][j] = INF;
        }
    }

    priority_queue<Node, vector<Node>, CompareNode> pq;
    pq.push(Node(startX, startY, 0));
    distance[startX][startY] = 0;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.x == endX && current.y == endY) {
            return distance[endX][endY];
        }

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < MAZE_ROWS && ny >= 0 && ny < MAZE_COLS && mazeLayout[nx][ny] != 1) {
                int newDist = current.dist + 1;
                if (newDist < distance[nx][ny]) {
                    distance[nx][ny] = newDist;
                    pq.push(Node(nx, ny, newDist));
                }
            }
        }
    }

    return -1; // No path found
}

int main() {
    int startingRow = 0;
    int startingCol = 0;

    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    // Initially, display a black screen
    cleardevice();

    renderMaze();

    cout << "Click anywhere to solve the maze using Dijkstra's algorithm." << endl;

    int x, y;
    int endX = -1, endY = -1;

    for (int i = 0; i < MAZE_ROWS; i++) {
        for (int j = 0; j < MAZE_COLS; j++) {
            if (mazeLayout[i][j] == 2) {
                endX = i;
                endY = j;
                break;
            }
        }
        if (endX != -1) break;
    }

    while (!goalFound) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            goalFound = 0;
            cleardevice();
            renderMaze();

            int shortestPathLength = dijkstra(startingRow, startingCol, endX, endY);

            if (shortestPathLength > 0) {
                cout << "Shortest path length: " << shortestPathLength << endl;
            } else {
                cout << "No path to the goal found!" << endl;
            }

            customDelay(100);
            renderMaze();
            drawPathOnMaze();
        }
    }

    getch();
    closegraph();

    return 0;
}
