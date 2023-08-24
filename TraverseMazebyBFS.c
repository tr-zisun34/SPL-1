#include <stdio.h>
#include <stdlib.h>  // For using queue

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

// Structure to represent a queue node
struct QueueNode {
    int i, j;
    struct QueueNode* next;
};

// Structure to represent a queue
struct Queue {
    struct QueueNode *front, *rear;
};

// Function to create a new queue node
struct QueueNode* newNode(int i, int j) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->i = i;
    temp->j = j;
    temp->next = NULL;
    return temp;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Function to enqueue a node to the rear of the queue
void enqueue(struct Queue* q, int i, int j) {
    struct QueueNode* temp = newNode(i, j);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// Function to dequeue a node from the front of the queue
struct QueueNode* dequeue(struct Queue* q) {
    if (q->front == NULL) return NULL;
    struct QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    return temp;
}

// Function to perform BFS
void bfs(int startI, int startJ) {
    struct Queue* queue = createQueue();
    enqueue(queue, startI, startJ);

    while (queue->front != NULL) {
        struct QueueNode* current = dequeue(queue);
        int i = current->i;
        int j = current->j;

        if (i < 0 || j < 0 || i >= ROWS || j >= COLS || maze[i][j] == 1 || path[i][j] == 1) {
            free(current);
            continue;
        }

        path[i][j] = 1;

        if (maze[i][j] == 2) {
            found = 1;
            free(current);
            return;
        }

        enqueue(queue, i + 1, j);
        enqueue(queue, i, j + 1);
        enqueue(queue, i, j - 1);
        enqueue(queue, i - 1, j);

        free(current);
    }
}

int main() {
    int startI = 1;  // Starting row index
    int startJ = 1;  // Starting column index

    bfs(startI, startJ);

    if (found) {
        printf("Path to reach 2:\n");
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (path[i][j] == 1) printf("-> [%d,%d] ", i, j);
            }
            printf("\n");
        }
    } else {
        printf("Path to 2 not found!\n");
    }

    return 0;
}
