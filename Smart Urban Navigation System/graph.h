#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
using namespace std;

const int MAXV = 100; 
const double INF = 1e18;  


struct Edge {
    int to;           
    double distance;  
    double traffic;  
    double weather;   
};


extern int V, E;
extern string vertexName[MAXV];
extern double delay[MAXV];
extern vector<Edge> adjacency[MAXV];


int findVertexIndex(string name);
double getEdgeCost(Edge e);

#endif
