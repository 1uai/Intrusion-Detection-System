# Intrusion Detection System (IDS)

This project implements an Intrusion Detection System (IDS) that analyzes network traffic to detect malicious patterns using the Aho-Corasick algorithm for multi-pattern string matching. It also visualizes network communication paths as a graph using a DOT file export, leveraging the pcap library for packet capturing.

## 🛡️ Overview

- **Purpose**: Detect malicious patterns in network traffic logs and visualize communication between nodes.
- **Algorithms/Data Structures**:
  - Aho-Corasick algorithm for efficient multi-pattern matching.
  - Graph data structure to represent network connections.
- **Features**:
  - Parses network packets and identifies attacks based on predefined malicious patterns.
  - Builds and displays a directed graph of network traffic.
  - Exports the graph to a DOT file for visualization (e.g., with Graphviz).
  - Provides real-time alerts for detected patterns and clears benign packets.

## ⚙️ Prerequisites

- **Operating System**: Linux (tested on Ubuntu)
- **Dependencies**:
  ```bash
  sudo apt-get install libpcap-dev g++ hping3 graphviz


## **Quick Start**:
   ```bash
   git clone https://github.com/your-username/ids-project.git
   cd ids-project
   g++ -o ids main.cpp graph.cpp network_parser.cpp aho_corasick.cpp -lpcap
   ```
**Send a Packet to IP**
   ```bash
     sudo hping3 -1 -d 100 -E payload.txt 127.0.0.1
```
**Note:** Replace 135.0.0.2 with your actual IP address. Use 127.0.0.1 for local testing.
Use this in another terminal or system dont close it
**Run the IDS**
   ```bash
     sudo ./ids
```
**Generate and View Graph**
```bash
dot -Tpng network_graph.dot -o network_graph.png
```









