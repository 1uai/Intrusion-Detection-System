#ifndef NETWORK_PARSER_H
#define NETWORK_PARSER_H

#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct Connection {
    string srcIP;
    string dstIP;
    uint16_t protocol;
    time_t timestamp;
    uint32_t pktLength;
    string payload; // Added to store packet payload
};

extern vector<Connection> capturedConnections;

void packetHandler(u_char* args, const struct pcap_pkthdr* header, const u_char* packet);
void loadPatterns(const string& filename); // Add this line

#endif