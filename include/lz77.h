#ifndef LZ77_H
#define LZ77_H

#include <vector>
#include <string>

struct Token {
    int offset;
    int length;
    char nextChar;
};

std::vector<Token> compressLZ77(std::string input, int windowSize = 20);

#endif