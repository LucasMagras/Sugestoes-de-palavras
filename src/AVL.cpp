#include "AVL.hpp"

AVL* insert(AVL* root, string word, int frequency) {
    if (root == nullptr) {
        return new AVL(word, frequency);
    }
    if (frequency < root->frequency) { // Insere na subárvore esquerda se a frequência for menor
        root->left = insert(root->left, word, frequency);
    } 
    else if (frequency > root->frequency) {
        root->right = insert(root->right, word, frequency);
    } 
    else { // Caso a frequência seja igual
       root->palavras.push_back(word);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

    // Casos de desequilíbrio
    if (balance > 1) {
        if (frequency < root->left->frequency) {
            // Rotação simples à direita
            return rightRotate(root);
        } 
        else {
            // Rotação dupla à esquerda-direita
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (frequency > root->right->frequency) {
            // Rotação simples à esquerda
            return leftRotate(root);
        } 
        else {
            // Rotação dupla à direita-esquerda
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}
int getHeight(AVL* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}
int getBalanceFactor(AVL* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}
AVL* rightRotate(AVL* y) {
    AVL* x = y->left;
    AVL* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}
AVL* leftRotate(AVL* x) {
    AVL* y = x->right;
    AVL* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}