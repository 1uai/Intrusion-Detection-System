#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct ACNode {
    unordered_map<char, ACNode*> children;
    ACNode* failure;
    vector<string> outputs;
    ACNode() : failure(nullptr) {}
    ~ACNode();
};

class AhoCorasick {
private:
    ACNode* root;
    void buildFailureLinks();
public:
    AhoCorasick() : root(new ACNode()) {}
    ~AhoCorasick();
    void addPattern(const string& pattern);
    void build();
    vector<pair<string, size_t>> search(const string& text);
};

#endif