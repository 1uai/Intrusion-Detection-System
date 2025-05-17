#include "network_parser.h"
#include "aho_corasick.h"
#include <iostream>
#include <fstream>

vector<Connection> capturedConnections;
AhoCorasick ac;

void loadPatterns(const string& filename) {
    ifstream in(filename);
    string pattern;
    while (getline(in, pattern)) {
        if (!pattern.empty()) {
            ac.addPattern(pattern);
        }
    }
    ac.build();
    in.close();
}

void packetHandler(u_char* args, const struct pcap_pkthdr* header, const u_char* packet) {
    struct ethhdr* eth = (struct ethhdr*)packet;

    if (ntohs(eth->h_proto) != ETH_P_IP)
        return;

    struct iphdr* ip = (struct iphdr*)(packet + sizeof(struct ethhdr));
    struct in_addr src, dst;
    src.s_addr = ip->saddr;
    dst.s_addr = ip->daddr;

    string srcIP = inet_ntoa(src);
    string dstIP = inet_ntoa(dst);
    uint16_t protocol = ip->protocol;

    time_t timestamp = header->ts.tv_sec;
    uint32_t pktLength = header->len;

    // Extract payload (adjusted for ICMP with ICMP header offset)
    const u_char* payload = packet + sizeof(struct ethhdr) + (ip->ihl * 4);
    uint32_t payloadLength = pktLength - (sizeof(struct ethhdr) + ip->ihl * 4);
    if (protocol == IPPROTO_ICMP && payloadLength > 8) { // Skip ICMP header (8 bytes)
        payload += 8; // Move past ICMP header
        payloadLength -= 8;
        payloadLength = min(payloadLength, 100u); // Limit to 100 bytes
        string payloadStr;
        for (uint32_t i = 0; i < payloadLength; ++i) {
            if (isprint(payload[i])) {
                payloadStr += (char)payload[i];
            } else {
                payloadStr += '.';
            }
        }
        // Run Aho-Corasick matching on payload
        auto matches = ac.search(payloadStr);
        if (matches.empty()) {
            cout << "CLEAR: Packet from " << srcIP << " to " << dstIP << " contains no malicious patterns.\n";
        } else {
            for (const auto& match : matches) {
                cout << "ALERT: Detected pattern '" << match.first
                    << "' at position " << match.second
                    << " in packet from " << srcIP << " to " << dstIP << "\n";
            }
        }
    }

    capturedConnections.push_back({srcIP, dstIP, protocol, timestamp, pktLength, ""}); // Empty payload if not ICMP

    cout << "Time: " << ctime(&timestamp)
        << "From: " << srcIP
        << " -> To: " << dstIP
        << " | Proto: " << (int)protocol
        << " | Size: " << pktLength << " bytes\n";
}