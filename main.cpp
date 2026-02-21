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

    double ratio = (double)estimatedCompressedSize / input.size();

    cout << "Compression Ratio (naive): " << ratio << endl;

    vector<string> symbols;

for (auto &t : compressed) {
    if (t.offset == 0) {
        symbols.push_back(string(1, t.nextChar));
    } else {
        string matchSymbol = "M_" + to_string(t.length) + "_" + to_string(t.offset);
        symbols.push_back(matchSymbol);
    }
}

auto codes = buildHuffmanCodes(symbols);

string encoded = encodeWithHuffman(symbols, codes);

cout << "Encoded Bit Length: " << encoded.size() << " bits\n";
cout << "Approx Compressed Size: " << encoded.size() / 8.0 << " bytes\n";

    string decompressed = decompressLZ77(compressed);

    if (decompressed == input)
        cout << "Reversible Compression Confirmed\n";
    else
        cout << "Error in Decompression\n";

   

    return 0;
}
   