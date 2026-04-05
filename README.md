#  Lossless Compression Engine (LZ77 + Huffman)

## 📌 Overview

This project implements a **lossless data compression system from scratch in C++**, combining:

* **LZ77 Compression** (removes redundancy using sliding window)
* **Huffman Coding** (reduces data size using variable-length encoding)

The system performs **end-to-end compression and decompression**, including **binary file storage**, similar to real-world compression algorithms like DEFLATE.

---

## 🧠 Architecture

```
Input File
   ↓
LZ77 Compression
   ↓
Symbol Stream
   ↓
Huffman Encoding
   ↓
Bit Packing
   ↓
Compressed Binary File (.bin)
   ↓
--------------------------------
   ↓
Read Binary File
   ↓
Bit Unpacking
   ↓
Huffman Decoding
   ↓
Symbol Reconstruction
   ↓
LZ77 Decompression
   ↓
Original File Restored
```

---

## ✨ Features

*  LZ77 compression using sliding window technique
*  Huffman coding (tree-based entropy encoding)
*  Bit-level encoding (efficient storage)
*  Binary file writing & reading
*  Full reversible pipeline (lossless compression)
*  Modular C++ architecture (headers + source files)
*  Error handling for file operations

---

## 🛠 Tech Stack

* **Language:** C++
* **Concepts Used:**

  * Data Structures (Heap, Tree, Hash Map)
  * Greedy Algorithms (Huffman)
  * Sliding Window Technique (LZ77)
  * Bit Manipulation
  * File Handling (Binary I/O)

---

## 📂 Project Structure

```
Zip Compressor/
│
├── include/
│   ├── lz77.h
│   ├── huffman.h
│
├── src/
│   ├── lz77.cpp
│   ├── huffman.cpp
│
├── test/
│   ├── sample.txt
│
├── main.cpp
└── compressed.bin
```

---

## ⚙️ How to Run

### 🔹 Compile

```bash
g++ src/lz77.cpp src/huffman.cpp main.cpp -o compressor
```

### 🔹 Run

```bash
./compressor
```

### 🔹 Input

Enter file name inside `test/` folder:

```
sample.txt
```

---

## 📊 Sample Output

```
Original Size: 50 bytes
Number of LZ77 Tokens: 10
Encoded Bit Length: 48 bits
Approx Compressed Size: 6 bytes

✔ Reversible Compression Confirmed
✔ Huffman Decoding Successful
✔ FULL PIPELINE SUCCESS
```

---

## 📈 Key Concepts

### 🔹 LZ77 Compression

* Uses sliding window
* Replaces repeated patterns with `(offset, length, nextChar)`

### 🔹 Huffman Coding

* Assigns shorter codes to frequent symbols
* Uses binary tree (min-heap based)

### 🔹 Bit Packing

* Converts bitstring → bytes
* Stores actual bit length to handle padding

---

## 🚧 Limitations

* Uses simplified symbol encoding (not fully optimized like production systems)
* No adaptive Huffman or advanced dictionary structures
* Compression ratio not as high as industrial tools (e.g., ZIP, 7z)

---

## 🚀 Future Improvements

*  Optimize LZ77 using hash-based matching
*  Separate encoding of length & offset (like DEFLATE)
*  CLI tool support (`compress input.txt output.bin`)
*  GUI / Web-based visualizer
*  Performance benchmarking vs standard compressors

---

## 🏆 Learning Outcomes

* Deep understanding of compression algorithms
* Practical implementation of LZ77 & Huffman
* Bit-level data handling
* System design thinking for real-world tools

---

## 👨‍💻 Author

**Ravi Ranjan**
B.Tech CSE | Software Developer Aspirant

---

## ⭐ If you found this useful

Give this repo a ⭐ and share!
