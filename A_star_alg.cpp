#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>  // for getch() function
#include <graphics.h>

#define ROWS 16
#define COLS 21
#define CELL_SIZE 30

// Define a structure to represent a node on the grid
typedef struct {
    int x, y;   // Coordinates of the node
    int g;      // Cost from start node to this node
    int h;      // Heuristic cost (estimated cost to goal)
    int f;      // Total cost (g + h)
} Node;

// Function to calculate the Manhattan distance heuristic between two nodes
int calculateManhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Function to check if a given cell is valid (within the grid)
bool isValidCell(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS);
}

// Function to draw a rectangle for a cell
void drawCell(int x, int y, int color) {
    setfillstyle(SOLID_FILL, color);
    bar(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
}

// Function to implement the A* algorithm and visualize the path
bool aStar(int grid[ROWS][COLS], Node start, Node goal) {
    // Initialize graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Create open and closed lists
    Node openList[ROWS * COLS];
    Node closedList[ROWS * COLS];

    // Initialize counters
    int openCount = 0;
    int closedCount = 0;

    // Add the start node to the open list
    openList[openCount++] = start;

    while (openCount > 0) {
        // Find the node with the lowest f value in the open list
        int currentIndex = 0;
        for (int i = 1; i < openCount; i++) {
            if (openList[i].f < openList[currentIndex].f) {
                currentIndex = i;
            }
        }

        // Remove the current node from the open list
        Node current = openList[currentIndex];
        openCount--;
        for (int i = currentIndex; i < openCount; i++) {
            openList[i] = openList[i + 1];
        }

        // Mark the current node as traversed
        grid[current.x][current.y] = 2;

        // Draw the grid with updated cells
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (grid[i][j] == 1) {
                    drawCell(i, j, BLUE);  // Obstacle
                } else if (grid[i][j] == 2) {
                    drawCell(i, j, LIGHTGREEN);  // Traversed path
                } else {
                    drawCell(i, j, RED);  // Unexplored
                }
            }
        }

        // Delay for visualization (you can adjust this)
        delay(100);

        // Check if we have reached the goal
        if (current.x == goal.x && current.y == goal.y) {
            closegraph();
            return true;
        }

        // Generate and consider the neighbors of the current node
        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};
        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            // Check if the neighbor is valid and not in the closed list
            if (isValidCell(newX, newY) && grid[newX][newY] != 1) {
                Node neighbor;
                neighbor.x = newX;
                neighbor.y = newY;
                neighbor.g = current.g + 1;
                neighbor.h = calculateManhattanDistance(newX, newY, goal.x, goal.y);
                neighbor.f = neighbor.g + neighbor.h;

                // Check if the neighbor is already in the open list with a lower f value
                bool inOpenList = false;
                for (int j = 0; j < openCount; j++) {
                    if (openList[j].x == neighbor.x && openList[j].y == neighbor.y && openList[j].f <= neighbor.f) {
                        inOpenList = true;
                        break;
                    }
                }

                // If not in the open list, add it
                if (!inOpenList) {
                    openList[openCount++] = neighbor;
                }
            }
        }
    }

    closegraph();
    printf("Path not found!\n");
    return false;
}

int main() {
    int grid[ROWS][COLS] = {
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

    Node start = {0, 0, 0, 0, 0};
    Node goal = {15, 15, 0, 0, 0};

    if (aStar(grid, start, goal)) {
        printf("Path found!\n");
    }

    getch();  // Wait for a key press
    return 0;
}
