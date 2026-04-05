#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct HuffmanNode {
    string symbol;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(string s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
};

unordered_map<string, int> buildFrequencyTable(const vector<string>& symbols);

unordered_map<string, string> generateCodes(HuffmanNode* root);

string encodeWithHuffman(const vector<string>& symbols,
                         const unordered_map<string, string>& codes);

HuffmanNode* buildHuffmanTree(const vector<string>& symbols);

string decodeWithHuffman(const string& encoded,
                         HuffmanNode* root);
void freeTree(HuffmanNode* root);
#endif