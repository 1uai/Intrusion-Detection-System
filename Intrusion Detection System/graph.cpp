// graph.cpp
#include "graph.h"
#include "network_parser.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<string, vector<pair<string, uint32_t>>> adjList;
unordered_set<string> nodes;

void Graph::addEdge(const string& src, const string& dst, uint32_t weight) {
    adjList[src].push_back({dst, weight});
    nodes.insert(src);
    nodes.insert(dst);
}

void Graph::display() const {
    cout << "\n--- Communication Graph ---\n";
    for (const auto& pair : adjList) {
        for (const auto& neighbor : pair.second) {
            cout << pair.first << " --> " << neighbor.first
                << " (Bytes: " << neighbor.second << ")\n";
        }
    }
}

void Graph::exportToDOT(const string& filename) const {
    ofstream out(filename);
    out << "digraph NetworkGraph {\n";
    for (const auto& pair : adjList) {
        for (const auto& neighbor : pair.second) {
            out << "    \"" << pair.first << "\" -> \"" << neighbor.first
                << "\" [label=\"" << neighbor.second << " bytes\"];\n";
        }
    }
    out << "}\n";
    out.close();
    cout << "\nDOT file exported to: " << filename << "\n";
}

void buildGraphFromConnections(const vector<Connection>& connections, Graph& g) {
    for (const auto& conn : connections) {
        g.addEdge(conn.srcIP, conn.dstIP, conn.pktLength);
    }
}
