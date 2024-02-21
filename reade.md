# Huffman Project

## Introduction

Huffman coding, named after its inventor David Huffman, is a lossless data compression technique that assigns shorter codes to more frequent symbols and longer codes to less frequent symbols. This approach aims to minimize the average length of the encoded data, resulting in a compressed representation of the original information.

## Core Principles

1. Symbol Frequencies: The algorithm first analyzes the frequency of each symbol (character, letter, etc.) in the 
2. data. This information is crucial for assigning appropriate code lengths.
Building the Huffman Tree: Symbols are represented as leaf nodes in a binary tree. The algorithm iteratively merges the two symbols with the lowest frequencies into a parent node, assigning a 0 to the left branch and a 1 to the right branch. This process continues until a single root node remains, forming the Huffman tree.
3. Code Assignment: Each symbol's code is derived by traversing its path from the leaf node to the root, with 0s corresponding to left branches and 1s to right branches. More frequent symbols will have shorter paths, resulting in shorter codes.
4. Decoding: Decoding involves traversing the Huffman tree based on the received code. Starting at the root, each 0 leads to the left child, and each 1 leads to the right child. When a leaf node is reached, the corresponding symbol is identified and added to the decoded data.

## Implementation Steps

- Calculate symbol frequencies.
- Create a priority queue with leaf nodes representing symbols and their frequencies.
- Extract the two nodes with the lowest frequencies.
- Create a new parent node with these two nodes as children and a combined frequency.
- Insert the new parent node back into the priority queue.
- Repeat steps 3-5 until only one node remains (the root).
- Traverse the tree to assign codes to each symbol based on their paths.
- Encode the original data by replacing each symbol with its corresponding code.
- Decode the encoded data by traversing the Huffman tree based on the received codes.

## Applications

Huffman coding is widely used in various applications, including:

- File compression formats: ZIP, PNG, JPEG
- Network transmission protocols: HTTP, TCP/IP
- Data storage: Hard drives, SSDs
- Image and audio compression: JPEG, MP3
- Text compression: Dictionary encoding