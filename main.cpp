#include <iostream>
#include "include/lz77.h"
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

    string decompressed = decompressLZ77(compressed);

    if (decompressed == input)
        cout << " Reversible Compression Confirmed\n";
    else
        cout << " Error in Decompression\n";

    cout << "Number of LZ77 Tokens: " << compressed.size() << endl;

    return 0;
}
   