#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

struct Item {
    string palavra;
    int frequencia;

    Item(string str, int freq) : palavra(str), frequencia(freq) {}

    bool operator<(Item other) const {
        return frequencia > other.frequencia;
    }
};

struct Huffman {
    string word;
    int frequency;
    Huffman* left;
    Huffman* right;

    Huffman(string word, int frequency) : word(word), frequency(frequency), left(nullptr), right(nullptr) {}

    bool operator>(const Huffman& other) const {
        return frequency > other.frequency;
    }
};

Huffman* MakeHuffmanTree(priority_queue<Item>& heap);
void printHuffmanCodes(Huffman* root);

#endif