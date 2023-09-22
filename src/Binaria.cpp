#include "Binaria.hpp"

Binaria* insert(Binaria* root, string word, int frequency) {
    if (root == nullptr) {
        return new Binaria(word, frequency);
    }

    if (frequency < root->frequency) {
        root->left = insert(root->left, word, frequency);
    }

    else if(frequency > root->frequency){
        root->right = insert(root->right, word, frequency);
    }

    else{
        root->palavras.push_back(word);
    }

    return root;
}