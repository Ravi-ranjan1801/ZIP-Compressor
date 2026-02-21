#include "../include/huffman.h"
#include <queue>

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

unordered_map<string, int> buildFrequencyTable(const vector<string>& symbols) {
    unordered_map<string, int> freq;
    for (auto &s : symbols) {
        freq[s]++;
    }
    return freq;
}

void generateCodes(HuffmanNode* root,
                   string currentCode,
                   unordered_map<string, string>& codes) {

    if (!root) return;

    if (!root->left && !root->right) {
        codes[root->symbol] = currentCode;
        return;
    }

    generateCodes(root->left, currentCode + "0", codes);
    generateCodes(root->right, currentCode + "1", codes);
}

unordered_map<string, string> buildHuffmanCodes(const vector<string>& symbols) {

    unordered_map<string, int> freq = buildFrequencyTable(symbols);

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (auto &p : freq) {
        pq.push(new HuffmanNode(p.first, p.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* parent = new HuffmanNode("", left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    HuffmanNode* root = pq.top();

    unordered_map<string, string> codes;
    generateCodes(root, "", codes);

    return codes;
}

string encodeWithHuffman(const vector<string>& symbols,
                         const unordered_map<string, string>& codes) {

    string encoded = "";

    for (auto &s : symbols) {
        encoded += codes.at(s);
    }

    return encoded;
}