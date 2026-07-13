#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "phase2.h"
#include "phase3.h"
using namespace std;


bool bellmanFord(int source, double dist[], int parent[]) {
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[source] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;
            for (int j = 0; j < (int)adjacency[u].size(); j++) {
                Edge e = adjacency[u][j];
                double newDist = dist[u] + getEdgeCost(e);
                if (newDist < dist[e.to]) {
                    dist[e.to] = newDist;
                    parent[e.to] = u;
                }
            }
        }
    }

    for (int u = 0; u < V; u++) {
        if (dist[u] == INF) continue;
        for (int j = 0; j < (int)adjacency[u].size(); j++) {
            Edge e = adjacency[u][j];
            double newDist = dist[u] + getEdgeCost(e);
            if (newDist < dist[e.to]) {
                return false;
            }
        }
    }

    return true;
}

void runPhase3() {
    ifstream fin("sample_map.txt");
    if (!fin.is_open()) {
        cout << "Error: could not open sample_map.txt" << endl;
        return;
    }

    string line;
    getline(fin, line);
    for (int i = 0; i < V; i++) getline(fin, line);
    for (int i = 0; i < E; i++) getline(fin, line);

    string srcName, tgtName;
    fin >> srcName >> tgtName;
    fin.close();

    int source = findVertexIndex(srcName);
    int target = findVertexIndex(tgtName);

    if (source == -1 || target == -1) {
        cout << "Error: invalid source or target vertex name." << endl;
        return;
    }

    double dist[MAXV];
    int parent[MAXV];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[source] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;
            for (int j = 0; j < (int)adjacency[u].size(); j++) {
                Edge e = adjacency[u][j];
                double cost = getEdgeCost(e);
                if (dist[e.to] > dist[u] + cost) {
                    dist[e.to] = dist[u] + cost;
                    parent[e.to] = u;
                }
            }
        }
    }

    for (int u = 0; u < V; u++) {
        if (dist[u] == INF) continue;
        for (int j = 0; j < (int)adjacency[u].size(); j++) {
            Edge e = adjacency[u][j];
            double cost = getEdgeCost(e);
            if (dist[e.to] > dist[u] + cost) {
                cout << endl << "Bellman-Ford: NEGATIVE CYCLE FOUND" << endl;
                return;
            }
        }
    }

    cout << endl << "Bellman-Ford Shortest Path" << endl;
    cout << "Source: " << vertexName[source] << "   Target: " << vertexName[target] << endl;

    if (dist[target] >= INF) {
        cout << "No path exists from " << vertexName[source] << " to " << vertexName[target] << endl;
    } else {
        cout << "Minimum total cost: " << dist[target] << endl;
        printPath(source, target, parent);
    }
}
