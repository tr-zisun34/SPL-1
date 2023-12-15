#include <iostream>

using namespace std;

const int MAX = 100; // Maximum number of nodes
const int INF = 1e9; // Infinity

void dijkstra(int graph[MAX][MAX], int n, int start) {
    int dist[MAX];
    bool visited[MAX];

    for (int i = 0; i < n; ++i) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[start] = 0;

    for (int i = 0; i < n - 1; ++i) {
        int u = -1;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "Shortest distances from node " << start << ":" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " << dist[i] << endl;
    }
}

int main() {
    int numOfNodes, start;
    cout << "Enter the number of nodes: ";
    cin >> numOfNodes;

    int graph[MAX][MAX];
    cout << "Enter the adjacency matrix:" << endl;
    for (int i = 0; i < numOfNodes; ++i) {
        for (int j = 0; j < numOfNodes; ++j) {
            cin >> graph[i][j];
        }
    }

    cout << "Enter the starting node: ";
    cin >> start;

    dijkstra(graph, numOfNodes, start);

    return 0;
}
