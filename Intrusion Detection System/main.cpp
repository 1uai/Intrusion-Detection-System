#include "network_parser.h"
#include "graph.h"
#include <pcap.h>
#include <iostream>
using namespace std;

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];

    // Load malicious patterns
    loadPatterns("patterns.txt");
    cout << "Loaded malicious patterns for intrusion detection.\n";

    // Explicitly use the loopback interface (lo)
    const char* dev = "lo";
    cout << "Using device: " << dev << endl;

    // Open the selected device
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        cerr << "Couldn't open device " << dev << ": " << errbuf << endl;
        return 1;
    }

    cout << "Starting packet capture...\n";
    pcap_loop(handle, 10, packetHandler, nullptr); // Capture 10 packets

    pcap_close(handle);
    cout << "Capture complete.\n";

    // Graph logic
    Graph g;
    buildGraphFromConnections(capturedConnections, g);
    g.display();
    g.exportToDOT("network_graph.dot");

    return 0;
}