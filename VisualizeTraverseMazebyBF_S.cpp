#include <iostream>
#include <queue>

#define ROWS 16
#define COLS 21

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
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1},
};

int found = 0;
int path[ROWS][COLS];

struct QueueNode {
    int i, j;
    QueueNode* next;
};

struct Queue {
    QueueNode* front = NULL, *rear = NULL;
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
    int startI = 0;
    int startJ = 0;

    bfs(startI, startJ);

    if (found) {
        std::cout << "Path to reach 2:" << std::endl;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (path[i][j] == 1) std::cout << "-> [" << i << "," << j << "] ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Path to 2 not found!" << std::endl;
    }

    return 0;
}
