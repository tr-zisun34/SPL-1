#include <iostream>
#include <queue>
#include <graphics.h>

#define ROWS 16
#define COLS 21

int maze[ROWS][COLS] = {
    // ... (same maze initialization)
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

int found = 0;
int path[ROWS][COLS];

struct QueueNode {
    int i, j;
    struct QueueNode* next;
};

struct Queue {
    QueueNode *front, *rear;
};

QueueNode* newNode(int i, int j) {
    QueueNode* temp = new QueueNode;
    temp->i = i;
    temp->j = j;
    temp->next = NULL;
    return temp;
}

Queue* createQueue() {
    Queue* q = new Queue;
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, int i, int j) {
    QueueNode* temp = newNode(i, j);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

QueueNode* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    return temp;
}

void bfs(int startI, int startJ) {
    Queue* queue = createQueue();
    enqueue(queue, startI, startJ);

    while (queue->front != NULL) {
        QueueNode* current = dequeue(queue);
        int i = current->i;
        int j = current->j;

        if (i < 0 || j < 0 || i >= ROWS || j >= COLS || maze[i][j] == 1 || path[i][j] == 1) {
            delete current;
            continue;
        }

        path[i][j] = 1;

        if (maze[i][j] == 2) {
            found = 1;
            delete current;
            return;
        }

        enqueue(queue, i + 1, j);
        enqueue(queue, i, j + 1);
        enqueue(queue, i, j - 1);
        enqueue(queue, i - 1, j);

        delete current;
    }
}

int main() {
    int startI = 1;  // Starting row index
    int startJ = 1;  // Starting column index

    bfs(startI, startJ);

    // Visualization using graphics.h
    initwindow(640, 480); // Initialize graphics window

    int cellSize = 30; // Size of each cell in pixels

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 1) {
                setfillstyle(SOLID_FILL, RED);
            } else if (path[i][j] == 1) {
                setfillstyle(SOLID_FILL, GREEN);
            } else if (maze[i][j] == 2) {
                setfillstyle(SOLID_FILL, BLUE);
            } else {
                setfillstyle(SOLID_FILL, WHITE);
            }

            bar(j * cellSize, i * cellSize, (j + 1) * cellSize, (i + 1) * cellSize);
        }
    }

    delay(5000); // Pause for 5 seconds

    closegraph(); // Close graphics window

    return 0;
}
