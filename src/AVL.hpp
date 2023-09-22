#ifndef AVL_HPP
#define AVL_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct AVL {
    string word;
    int frequency;
    AVL* left;
    AVL* right;
    int height;

    vector<string> palavras;

    AVL(string w, int f): word(w), frequency(f), left(nullptr), right(nullptr), height(1) {}
};

AVL* insert(AVL* root, string word, int frequency);
int getHeight(AVL* node);
int getBalanceFactor(AVL* node);
AVL* rightRotate(AVL* y);
AVL* leftRotate(AVL* x);

#endif