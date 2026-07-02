#include <iostream>
#include <vector>
#include "graph.h"
#include "phase2.h"
using namespace std;

void dijkstra(int source, double dist[], int parent[]) {
    bool visited[MAXV];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }
    dist[source] = 0;

    for (int count = 0; count < V; count++) {

        int u = -1;
        double bestDist = INF;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < bestDist) {
                bestDist = dist[i];
                u = i;
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = true;

        for (int i = 0; i < (int)adjacency[u].size(); i++) {
            Edge e = adjacency[u][i];
            double newDist = dist[u] + getEdgeCost(e);

            if (newDist < dist[e.to]) {
                dist[e.to] = newDist;
                parent[e.to] = u;
            }
        }
    }
}

void printPath(int source, int target, int parent[]) {
    vector<int> path;

    int current = target;
    while (current != -1) {
        path.push_back(current);
        if (current == source) {
            break;
        }
        current = parent[current];
    }

    cout << "Path: ";
    for (int i = (int)path.size() - 1; i >= 0; i--) {
        cout << vertexName[path[i]];
        if (i != 0) {
            cout << " -> ";
        }
    }
    cout << endl;
}
