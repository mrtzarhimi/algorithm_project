#include <iostream>
#include <fstream>
#include "graph.h"
#include "phase1.h"
using namespace std;

bool readMapFile(string fileName, int &sourceIndex, int &targetIndex) {
    ifstream fin(fileName.c_str());

    if (!fin.is_open()) {
        cout << "Error: could not open file " << fileName << endl;
        return false;
    }

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
            cout << "Error: edge uses a vertex name that was not defined." << endl;
            return false;
        }

        Edge e;
        e.to = v;
        e.distance = d;
        e.traffic = t;
        e.weather = w;

        adjacency[u].push_back(e);
    }

    string sourceName, targetName;
    fin >> sourceName >> targetName;

    sourceIndex = findVertexIndex(sourceName);
    targetIndex = findVertexIndex(targetName);

    if (sourceIndex == -1 || targetIndex == -1) {
        cout << "Error: unknown source or target vertex." << endl;
        return false;
    }

    fin.close();
    return true;
}

void printGraph() {
    for (int u = 0; u < V; u++) {
        cout << vertexName[u] << " (delay = " << delay[u] << ")" << endl;

        for (int i = 0; i < (int)adjacency[u].size(); i++) {
            Edge e = adjacency[u][i];
            cout << "   -> " << vertexName[e.to]
                 << " | distance = " << e.distance
                 << " traffic = " << e.traffic
                 << " weather = " << e.weather
                 << " | cost = " << getEdgeCost(e) << endl;
        }
    }
}
