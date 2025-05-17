// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <pcap.h>
using namespace std;

struct Connection; // Forward declaration

class Graph {
public:
    void addEdge(const string& src, const string& dst, uint32_t weight);
    void display() const;
    void exportToDOT(const string& filename = "network_graph.dot") const;
};

void buildGraphFromConnections(const vector<Connection>& connections, Graph& g);

#endif
