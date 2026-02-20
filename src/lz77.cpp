#include "../include/lz77.h"
using namespace std;

vector<Token> compressLZ77(string input, int windowSize) {
    vector<Token> output;
    int n = input.length();

    for (int i = 0; i < n; ) {
        int bestLength = 0;
        int bestOffset = 0;

        int start = max(0, i - windowSize);

        for (int j = start; j < i; j++) {
            int length = 0;

            while (i + length < n &&
                   input[j + length] == input[i + length]) {
                length++;
            }

            if (length > bestLength) {
                bestLength = length;
                bestOffset = i - j;
            }
        }

        char nextChar = (i + bestLength < n) ? input[i + bestLength] : '\0';

        output.push_back({bestOffset, bestLength, nextChar});

        i += bestLength + 1;
    }

    return output;
}

string decompressLZ77(vector<Token> tokens) {
    string output;

    for (auto &t : tokens) {

        if (t.offset == 0) {
            if (t.nextChar != '\0')
                output += t.nextChar;
        }
        else {
            int start = output.size() - t.offset;

            for (int i = 0; i < t.length; i++) {
                output += output[start + i];
            }

            if (t.nextChar != '\0')
                output += t.nextChar;
        }
    }

    return output;
}