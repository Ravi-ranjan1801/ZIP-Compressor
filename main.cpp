#include <iostream>
#include "include/lz77.h"
#include "include/huffman.h"
#include <fstream>
#include <sstream>

using namespace std;

string readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file!\n";
        exit(1);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

vector<string> splitSymbols(const string& decoded) {
    vector<string> result;
    string temp = "";

    for (char c : decoded) {
        if (c == '|') {
            if (!temp.empty())
                result.push_back(temp);
            temp = "";
        } else {
            temp += c;
        }
    }
    return result;
}

vector<unsigned char> bitStringToBytes(const string& bits) {
    vector<unsigned char> bytes;

    for (int i = 0; i < bits.size(); i += 8) {
        string byteStr = bits.substr(i, 8);
        while (byteStr.size() < 8) byteStr += '0';

        unsigned char byte = 0;
        for (int j = 0; j < 8; j++) {
            if (byteStr[j] == '1')
                byte |= (1 << (7 - j));
        }

        bytes.push_back(byte);
    }

    return bytes;
}

string bytesToBitString(const vector<unsigned char>& data) {
    string bits = "";

    for (unsigned char byte : data) {
        for (int i = 7; i >= 0; i--) {
            bits += ((byte >> i) & 1) ? '1' : '0';
        }
    }

    return bits;
}

void writeBinaryFile(const string& filename, 
                     const vector<unsigned char>& data,
                     int bitLength) {

    ofstream file(filename, ios::binary);

    // write bit length first (4 bytes)
    file.write((char*)&bitLength, sizeof(bitLength));

    // then write actual data
    file.write((char*)data.data(), data.size());
}

vector<unsigned char> readBinaryFile(const string& filename, int &bitLength) {
    ifstream file(filename, ios::binary);

    if (!file) {
        cerr << "Error opening compressed file\n";
        exit(1);
    }

    // read bit length first
    file.read((char*)&bitLength, sizeof(bitLength));

    vector<unsigned char> data(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    return data;
}

vector<Token> reconstructTokens(const vector<string>& symbols) {
    vector<Token> tokens;

    for (auto &s : symbols) {
        if (s.rfind("L_", 0) == 0) {
            char ch = s[2];
            tokens.push_back({0, 0, ch});
        } else if (s.rfind("M_", 0) == 0) {
            int length, offset;
            char nextChar;
            sscanf(s.c_str(), "M_%d_%d_%c", &length, &offset, &nextChar);
            if (nextChar == '#') nextChar = '\0';
            tokens.push_back({offset, length, nextChar});
        }
    }

    return tokens;
}

int main() {

    string filename;
    cout << "Enter file name (inside test folder): ";
    cin >> filename;

    string path = "test/" + filename;

    string input = readFile(path);

    cout << "\nOriginal Size: " << input.size() << " bytes\n";

    vector<Token> compressed = compressLZ77(input);
     cout << "Number of LZ77 Tokens: " << compressed.size() << endl; 

    size_t estimatedCompressedSize = compressed.size() * sizeof(Token);

    cout << "Estimated Compressed Size (naive struct storage): "
     << estimatedCompressedSize << " bytes\n";

    double ratio = input.empty() ? 0 : (double)estimatedCompressedSize / input.size();

    cout << "Compression Ratio (naive): " << ratio << endl;

  vector<string> symbols;

for (auto &t : compressed) {
    if (t.offset == 0) {
        symbols.push_back("L_" + string(1, t.nextChar));
    } else {
        string matchSymbol = "M_" + to_string(t.length) + "_" + to_string(t.offset) + "_" + string(1, t.nextChar == '\0' ? '#' : t.nextChar);
        symbols.push_back(matchSymbol);
    }
}

HuffmanNode* root = buildHuffmanTree(symbols);

if (!root) {
    cout << "No Huffman tree could be built.\n";
    return 0;
}

auto codes = generateCodes(root);

string encoded = encodeWithHuffman(symbols, codes);

auto bytes = bitStringToBytes(encoded);
writeBinaryFile("compressed.bin", bytes, encoded.size());
int bitLength;
auto readBytes = readBinaryFile("compressed.bin", bitLength);

string recoveredBits = bytesToBitString(readBytes);

// remove padding
recoveredBits = recoveredBits.substr(0, bitLength);

cout << "Compressed file written: compressed.bin\n";

string decodedStream = decodeWithHuffman(recoveredBits, root);



    string decompressed = decompressLZ77(compressed);

    if (decompressed == input)
        cout << "Reversible Compression Confirmed\n";
    else
        cout << "Error in Decompression\n";

  
string originalStream = "";
for (auto &s : symbols)
    originalStream += s + "|";

if (decodedStream == originalStream)
    cout << "Huffman Decoding Successful\n";
else
    cout << "Huffman Decoding Mismatch\n";

cout << "Encoded Bit Length: " << encoded.size() << " bits\n";
cout << "Approx Compressed Size: " << encoded.size() / 8.0 << " bytes\n";

 vector<string> decodedSymbols = splitSymbols(decodedStream);
vector<Token> reconstructedTokens = reconstructTokens(decodedSymbols);
string finalOutput = decompressLZ77(reconstructedTokens);

if (finalOutput == input)
    cout << "FULL PIPELINE SUCCESS\n";
else
    cout << "FULL PIPELINE FAILED\n";


      freeTree(root);
    return 0;
}

   