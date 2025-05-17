#include "aho_corasick.h"
//#include <algorithm>

ACNode::~ACNode() {
    for (auto& pair : children) {
        delete pair.second;
    }
}

AhoCorasick::~AhoCorasick() {
    delete root;
}

void AhoCorasick::addPattern(const string& pattern) {
    ACNode* current = root;
    for (char c : pattern) {
        if (!current->children.count(c)) {
            current->children[c] = new ACNode();
        }
        current = current->children[c];
    }
    current->outputs.push_back(pattern);
}

void AhoCorasick::buildFailureLinks() {
    queue<ACNode*> q;
    root->failure = root;
    for (auto& pair : root->children) {
        pair.second->failure = root;
        q.push(pair.second);
    }

    while (!q.empty()) {
        ACNode* current = q.front();
        q.pop();

        for (auto& pair : current->children) {
            char c = pair.first;
            ACNode* next = pair.second;
            q.push(next);

            ACNode* fail = current->failure;
            while (fail != root && !fail->children.count(c)) {
                fail = fail->failure;
            }
            if (fail->children.count(c)) {
                next->failure = fail->children[c];
            } else {
                next->failure = root;
            }

            next->outputs.insert(next->outputs.end(),
                            next->failure->outputs.begin(),
                            next->failure->outputs.end());
        }
    }
}

void AhoCorasick::build() {
    buildFailureLinks();
}

vector<pair<string, size_t>> AhoCorasick::search(const string& text) {
    vector<pair<string, size_t>> matches;
    ACNode* current = root;

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        while (current != root && !current->children.count(c)) {
            current = current->failure;
        }
        if (current->children.count(c)) {
            current = current->children[c];
        }

        for (const auto& output : current->outputs) {
            matches.emplace_back(output, i - output.length() + 1);
        }
    }

    return matches;
}