#ifndef READ_HPP
#define READ_HPP

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <locale>
#include "Binaria.hpp"
#include "AVL.hpp"
#include "Huffman.hpp"
#define k 11

using namespace std;

void printTrees(Binaria* binaria, AVL* avl);
void fake_main();
void leitura(string FileName, unordered_map<string, int>& frequencia, string StopWords);
void print_input(string FileName);
void PreencherHeap(unordered_map<string, int>& frequencia, priority_queue<Item>& heap, string Filename);
void ContarFrequenciaNoTexto(string palavra, string FileName);
void MakeTree(priority_queue<Item>& Heap, string palavraLidaDoArquivoInput);
string ConverterAcentuadasParaMinusculas(string num);
bool CaracterEstranho(string word);
bool VerificaInput(string FileName, string dataFilename, priority_queue<Item> Heap, unordered_map<string, int>& frequencia);

template <typename T>
void inordem(T *root){
    if (root != nullptr) {
        inordem(root->left);
        cout << root->word << " - Frequência: " << root->frequency << endl;
        for(auto w:root->palavras){
            cout << w << " - Frequência: " << root->frequency << endl;
        }
        inordem(root->right);
    }
}

template <typename T>
void preordem(T *root){
    if (root != nullptr) {
        cout << root->word << " - Frequência: " << root->frequency << endl;
        for(auto w:root->palavras){
            cout << w << " - Frequência: " << root->frequency << endl;
        }
        preordem(root->left);
        preordem(root->right);
    }
}

template <typename T>
void posordem(T *root){
    if (root != nullptr) {
        posordem(root->left);
        posordem(root->right);
        cout << root->word << " - Frequência: " << root->frequency << endl;
        for(auto w:root->palavras){
            cout << w << " - Frequência: " << root->frequency << endl;
        }
    }
}

#endif