#include "Huffman.hpp"

Huffman* MakeHuffmanTree(priority_queue<Item>& heap) {
    priority_queue<Item> copyHeap = heap;

    priority_queue<pair<int, Huffman*>, vector<pair<int, Huffman*>>, greater<pair<int, Huffman*>>> HuffmanPQueue;

    while (!copyHeap.empty()) {
        Item item = copyHeap.top();
        copyHeap.pop();

        Huffman* node = new Huffman(item.palavra, item.frequencia);
        HuffmanPQueue.push(make_pair(item.frequencia, node));
    }

    while (HuffmanPQueue.size() > 1) {
        pair<int, Huffman*> leftNode = HuffmanPQueue.top();
        HuffmanPQueue.pop();
        pair<int, Huffman*> rightNode = HuffmanPQueue.top();
        HuffmanPQueue.pop();

        Huffman* newNode = new Huffman("", leftNode.first + rightNode.first);
        newNode->left = leftNode.second;
        newNode->right = rightNode.second;

        HuffmanPQueue.push(make_pair(newNode->frequency, newNode));
    }

    return HuffmanPQueue.top().second;
}

void printHuffmanCodes(Huffman* root) {
    if (!root)
        return;

    queue<pair<Huffman*, string>> HuffmanQueue;
    HuffmanQueue.push({root, ""});

    while (!HuffmanQueue.empty()) {
        pair<Huffman*, string> currentPair = HuffmanQueue.front();
        HuffmanQueue.pop();

        Huffman* current = currentPair.first;
        string currentCode = currentPair.second;

        if (current->left == nullptr && current->right == nullptr) {
            cout << current->word << " - Codigo de Huffman: " << currentCode << std::endl;
        }

        if (current->left)
            HuffmanQueue.push({current->left, currentCode + "0"});

        if (current->right)
            HuffmanQueue.push({current->right, currentCode + "1"});
    }
}