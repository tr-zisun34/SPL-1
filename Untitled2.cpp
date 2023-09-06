#include <iostream>
#include <queue>
#include <vector>
#include <limits>

#define ROWS 16
#define COLS 21

int maze[ROWS][COLS] = {
    // ... (same as before)
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

int path[ROWS][COLS] = {
    0
};

struct Node {
    int vertex;
    int weight;
    Node(int v, int w) : vertex(v), weight(w) {}
};

struct CompareNodes {
    bool operator()(const Node& a, const Node& b) {
        return a.weight > b.weight;
    }
};

std::vector<std::vector<Node> > weightedGraph(ROWS * COLS);

void createWeightedGraph() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (path[i][j] == 1) {
                int currentVertex = i * COLS + j;
                if (i + 1 < ROWS && path[i + 1][j] == 1) {
                    weightedGraph[currentVertex].emplace_back((i + 1) * COLS + j, 1);
                }
                if (j + 1 < COLS && path[i][j + 1] == 1) {
                    weightedGraph[currentVertex].emplace_back(i * COLS + j + 1, 1);
                }
                // Add more edges based on the possible directions
            }
        }
    }
}

std::vector<int> dijkstra(int startVertex) {
    std::vector<int> dist(ROWS * COLS, std::numeric_limits<int>::max());
    dist[startVertex] = 0;

    std::priority_queue<Node, std::vector<Node>, CompareNodes> pq;
    pq.push(Node(startVertex, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        for (const Node& neighbor : weightedGraph[current.vertex]) {
            int newDist = dist[current.vertex] + neighbor.weight;
            if (newDist < dist[neighbor.vertex]) {
                dist[neighbor.vertex] = newDist;
                pq.push(neighbor);
            }
        }
    }

    return dist;
}

int main() {
    // ... (same as before)
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

    createWeightedGraph();
    std::vector<int> distances = dijkstra(startI * COLS + startJ);

    // Output distances to all reachable vertices
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (path[i][j] == 1) {
                int vertex = i * COLS + j;
                std::cout << "Distance to [" << i << "," << j << "]: " << distances[vertex] << std::endl;
            }
        }
    }

    return 0;
}
