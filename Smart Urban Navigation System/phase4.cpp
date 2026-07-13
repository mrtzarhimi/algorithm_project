#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "graph.h"
#include "phase4.h"
using namespace std;

bool shortestPath(int src, double dist[], int parent[]) {
    bool visited[MAXV];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }
    dist[src] = 0;

    for (int cnt = 0; cnt < V; cnt++) {
        int u = -1;
        double best = INF;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < best) {
                best = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = true;
        for (int j = 0; j < (int)adjacency[u].size(); j++) {
            Edge e = adjacency[u][j];
            double nd = dist[u] + getEdgeCost(e);
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                parent[e.to] = u;
            }
        }
    }

    return true;
}

void runPhase4() {
    ifstream fin("phase4_map.txt");
    if (!fin.is_open()) {
        cout << "Error: could not open phase4_map.txt" << endl;
        return;
    }

    for (int i = 0; i < V; i++) adjacency[i].clear();

    fin >> V >> E;
    for (int i = 0; i < V; i++) {
        fin >> vertexName[i] >> delay[i];
    }
    for (int i = 0; i < E; i++) {
        string startName, endName;
        double d, t, w;
        fin >> startName >> endName >> d >> t >> w;
        int u = findVertexIndex(startName);
        int v = findVertexIndex(endName);
        if (u == -1 || v == -1) {
            cout << "Error: invalid vertex in edge" << endl;
            return;
        }
        Edge e;
        e.to = v;
        e.distance = d;
        e.traffic = t;
        e.weather = w;
        adjacency[u].push_back(e);
    }

    string srcName;
    fin >> srcName;
    int source = findVertexIndex(srcName);
    if (source == -1) {
        cout << "Error: invalid source vertex" << endl;
        return;
    }

    vector<int> destinations;
    string destName;
    while (fin >> destName) {
        int idx = findVertexIndex(destName);
        if (idx != -1) destinations.push_back(idx);
    }
    fin.close();

    if (destinations.empty()) {
        cout << "No destinations specified." << endl;
        return;
    }

    cout << endl << "=== Phase 4: Nearest Neighbor TSP ===" << endl;
    cout << "Source: " << vertexName[source] << endl;
    cout << "Destinations: ";
    for (int d : destinations) cout << vertexName[d] << " ";
    cout << endl << endl;

    vector<int> route;
    route.push_back(source);
    int current = source;
    vector<bool> visited(V, false);
    int visitedCount = 0;
    double totalCost = 0;

    while (visitedCount < (int)destinations.size()) {
        double dist[MAXV];
        int parent[MAXV];
        shortestPath(current, dist, parent);

        int best = -1;
        double bestCost = INF;
        for (int x : destinations) {
            if (!visited[x] && dist[x] < bestCost) {
                bestCost = dist[x];
                best = x;
            }
        }

        if (best == -1) break;

        route.push_back(best);
        totalCost += bestCost;
        cout << vertexName[current] << " -> " << vertexName[best]
             << "  cost = " << bestCost << endl;
        current = best;
        visited[best] = true;
        visitedCount++;
    }

    double dist[MAXV];
    int parent[MAXV];
    shortestPath(current, dist, parent);
    double returnCost = dist[source];
    totalCost += returnCost;
    route.push_back(source);
    cout << vertexName[current] << " -> " << vertexName[source]
         << "  cost = " << returnCost << endl;

    cout << endl << "Nearest Neighbor Route:" << endl;
    for (int i = 0; i < (int)route.size(); i++) {
        cout << vertexName[route[i]];
        if (i != (int)route.size() - 1) cout << " -> ";
    }
    cout << endl;
    cout << "Total cost: " << totalCost << endl;
}
