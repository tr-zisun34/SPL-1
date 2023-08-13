#include <iostream>

using namespace std;

const int MAX_NODES = 1000;
const int INF = 1e9;

// Define a structure to represent edges
struct Edge {
    int to;
    int weight;
};

// Find the index of the node with the smallest distance
int findMinDistance(int distances[MAX_NODES], bool visited[MAX_NODES], int n) {
    int minDist = INF;
    int minIndex = -1;
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && distances[i] < minDist) {
            minDist = distances[i];
            minIndex = i;
        }
    }
    
    return minIndex;
}

// Dijkstra's algorithm function
void dijkstra(Edge graph[MAX_NODES][MAX_NODES], int n, int start, int distances[MAX_NODES]) {
    bool visited[MAX_NODES] = {false};
    distances[start] = 0;

    for (int i = 0; i < n - 1; ++i) {
        int current = findMinDistance(distances, visited, n);
        visited[current] = true;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && graph[current][j].to != -1) {
                int neighbor = graph[current][j].to;
                int weight = graph[current][j].weight;
                
                int potentialDistance = distances[current] + weight;

                if (potentialDistance < distances[neighbor]) {
                    distances[neighbor] = potentialDistance;
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    Edge graph[MAX_NODES][MAX_NODES];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            graph[i][j] = {-1, 0};
        }
    }

    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from][to] = {to, weight};
    }

    int startNode;
    cin >> startNode;

    int distances[MAX_NODES];
    for (int i = 0; i < n; ++i) {
        distances[i] = INF;
    }
    distances[startNode] = 0;

    dijkstra(graph, n, startNode, distances);

    for (int i = 0; i < n; ++i) {
        cout << "Distance from node " << startNode << " to node " << i << " is ";
        if (distances[i] == INF) {
            cout << "unreachable";
        } else {
            cout << distances[i];
        }
        cout << endl;
    }

    return 0;
}
