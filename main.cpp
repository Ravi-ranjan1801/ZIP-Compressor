#include <iostream>
#include "include/lz77.h"

using namespace std;

int main() {
    string input;

    cout << "Enter string: ";
    cin >> input;

    vector<Token> compressed = compressLZ77(input);

    cout << "\nCompressed Output:\n";
    for (auto t : compressed) {
        cout << "(" << t.offset << ", "
             << t.length << ", ";

        if (t.nextChar == '\0')
            cout << "NULL";
        else
            cout << t.nextChar;

        cout << ")\n";
    }
    string decompressed = decompressLZ77(compressed);

cout << "\nDecompressed Output:\n";
cout << decompressed << endl;

if (decompressed == input)
    cout << "\nReversible Compression Confirmed\n";
else
    cout << "\nError in Decompression\n";

    return 0;
}