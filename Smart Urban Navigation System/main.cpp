#include <iostream>
#include <string>
#include "graph.h"
#include "phase1.h"
#include "phase2.h"
#include "phase3.h"
#include "phase4.h"
using namespace std;

int main(int argc, char *argv[]) {
    string fileName = "sample_map.txt";

    int source, target;


    if (!readMapFile(fileName, source, target)) {
        return 1;
    }

    printGraph();

    double dist[MAXV];
    int parent[MAXV];
    dijkstra(source, dist, parent);

    cout << endl << "Dijkstra Shortest Path" << endl;
    cout << "Source: " << vertexName[source] << "   Target: " << vertexName[target] << endl;

    if (dist[target] >= INF) {
        cout << "No path exists from " << vertexName[source] << " to " << vertexName[target] << endl;
    } else {
        cout << "Minimum total cost: " << dist[target] << endl;
        printPath(source, target, parent);
    }

    
    runPhase3();

    runPhase4();
    return 0;
}
