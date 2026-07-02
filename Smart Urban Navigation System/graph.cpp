#include "graph.h"

int V, E;
string vertexName[MAXV];
double delay[MAXV];
vector<Edge> adjacency[MAXV];

int findVertexIndex(string name) {
    for (int i = 0; i < V; i++) {
        if (vertexName[i] == name) {
            return i;
        }
    }
    return -1;
}

double getEdgeCost(Edge e) {
    return e.distance * e.traffic * e.weather + delay[e.to];
}
