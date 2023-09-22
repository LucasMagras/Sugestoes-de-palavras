#ifndef BINARIA_HPP
#define BINARIA_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Binaria {
    string word;
    int frequency;
    Binaria* left;
    Binaria* right;

    vector<string> palavras;

    Binaria(string word, int freq) : word(word), frequency(freq),  left(nullptr), right(nullptr) {}
};

Binaria* insert(Binaria* root, string word, int frequency);

#endif