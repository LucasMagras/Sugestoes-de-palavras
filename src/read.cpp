#include "read.hpp"

void fake_main() 
{
    string StopWords("dataset/stopwords.txt");
    string dataInput("dataset/input.txt");
    vector<string> DataFileNames;
    vector <unordered_map<string,int>> frequencias(6);
    vector <priority_queue<Item>> heaps(6);
    ofstream output("output.txt");

    for(auto Name:{"politica","globalizacao","filosofia","filosofia2","ti","ti2"}){
        string str("dataset/");
        str.append(Name).append(".txt");
        DataFileNames.push_back(str);
    }

    cout << endl << "PROCESSANDO E ESCREVENDO NO ARQUIVO DE SAIDA..." << endl;
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf()); 

    for(int i = 0; i<6 ; i++){
        leitura(DataFileNames[i], frequencias[i], StopWords);
        PreencherHeap(frequencias[i], heaps[i], DataFileNames[i]);
    }

    print_input(dataInput);

    for(int i = 0; i<6 ; i++){
        VerificaInput(dataInput, DataFileNames[i], heaps[i], frequencias[i]);
    }

    cout.rdbuf(coutbuf);
    output.close();
}

void leitura(const string FileName, unordered_map<string, int>& frequencia, string StopWords)
{   
    string word, line;
    ifstream dataFile(FileName);
    ifstream StopWordsFile(StopWords);

    if (!dataFile.is_open()) {
        cout << "NAO FOI POSSIVEL ABRIR OS ARQUIVOS !!! " << endl;
    }

    while (getline(dataFile, line)) { // le cada linha do arquivo de dados
        stringstream ss(line); // cria um fluxo de string a partir da linha lida
        string token; // variável para armazenar cada token (palavra) extraído da linha
        while (ss >> token) { // le cada token (palavra) do fluxo de string
            token.erase(remove_if(token.begin(), token.end(), ::ispunct), token.end());  // remove sinais de pontuação do token
            transform(token.begin(), token.end(), token.begin(), ::tolower); // transforma para letras minusculas
            token = ConverterAcentuadasParaMinusculas(token); // transforma os caracteres acentuados para minusculos
            if (!token.empty() && CaracterEstranho(token)){ // evita adicionar espaços vazios na hash e trata o travessao
                frequencia[token]++; // incrementa a palavra e a frequência dela na hash
                // wordsInDataFile.insert(token);
            }
        }
    }

    while (getline(StopWordsFile, line)) { // excluindo as stop words da hash
        stringstream ss(line);
        string token;
        while (ss >> token) {
            frequencia.erase(token); // remove as palavras do arquivo de stopwords da hash
        }
    }
}

void print_input(string FileName){
    ifstream input(FileName);
    string palavra;

    if (!input.is_open()) {
        cout << "Não foi possível abrir o arquivo: " << FileName << endl;
        return;
    }

    cout << endl << "Palavras no arquivo 'input.txt' " << endl;
    while (input >> palavra) {
        cout << palavra << " " << endl;
    }

    input.close();
}

void PreencherHeap(unordered_map<string, int>& frequencia, priority_queue<Item>& heap, string Filename)
{
    cout << endl << "Heap com os top k elementos mais frequentes no texto '" << Filename << endl;
    for (std::unordered_map<string, int>::value_type pair: frequencia) { // preenche a heap com os primeiros k elementos da hash
        if (heap.size() < k) {
            heap.push(Item(pair.first, pair.second));
        } 
        else if (pair.second > heap.top().frequencia) {
            heap.pop();
            heap.push(Item(pair.first, pair.second));
        }
    }

    priority_queue<Item> heapCopy = heap;
    while (!heapCopy.empty()) {
        cout << heapCopy.top().palavra << " - Frequência: " << heapCopy.top().frequencia << endl;
        heapCopy.pop();
    }

    cout << endl << "----------------------------------------------------------------------------------------" << endl;
}

bool VerificaInput(string FileName, string dataFileName, priority_queue<Item> Heap, unordered_map<string, int>& frequencia) {
    ifstream inputFile(FileName);
    ifstream dataFile(dataFileName);
    vector <string> PalavrasInexistentes;

    if (!inputFile.is_open()) {
        cout << "NAO FOI POSSIVEL ABRIR O ARQUIVO DE ENTRADA !!! " << endl;
        return false;
    }

    cout << endl << "----------------------------------------------------------------------------------------" << endl;
    cout << endl << "ARQUIVO QUE ESTA SENDO ANALISADO : " << dataFileName << endl;

    string token;
    while (inputFile >> token) {
        token.erase(remove_if(token.begin(), token.end(), ::ispunct), token.end());
        transform(token.begin(), token.end(), token.begin(), ::tolower);
        token = ConverterAcentuadasParaMinusculas(token);
        if (!token.empty() && CaracterEstranho(token)) {
            bool foundInDataFile = (frequencia.find(token) != frequencia.end());
            if (foundInDataFile) {
                ContarFrequenciaNoTexto(token,dataFileName);
                MakeTree(Heap,token);
            }
            else {
                PalavrasInexistentes.push_back(token);
            }
        }
    }

    cout << endl << "Palavras não encontradas no arquivo de texto:" << endl;
    for (string notFound : PalavrasInexistentes) {
        cout << notFound << endl;
    }

    return true;
}

void MakeTree(priority_queue<Item>& Heap, string palavraLidaDoArquivoInput) {
    Binaria* tree = nullptr;
    AVL* avl = nullptr;
    Huffman* huff = nullptr;
    priority_queue<Item> heapCopy = Heap;

     while (!heapCopy.empty()) {
        Item item = heapCopy.top();
        heapCopy.pop();

        if (item.palavra == palavraLidaDoArquivoInput) {
            if (!heapCopy.empty()) {
                item = heapCopy.top();
                heapCopy.pop();
                tree = insert(tree, item.palavra, item.frequencia);
                avl = insert(avl, item.palavra, item.frequencia);
            } 
            else {
                break;
            }
        } 
        else {
            tree = insert(tree, item.palavra, item.frequencia);
            avl = insert(avl, item.palavra, item.frequencia);
        }
    }

    huff = MakeHuffmanTree(Heap);

    printTrees(tree, avl);

    cout << endl << "Arvore de Huffman contendo as palavras mais frequentes para este arquivo :" << endl << endl;
    printHuffmanCodes(huff);
}


void printTrees(Binaria* binaria, AVL* avl) {
    
    cout << endl << "Arvore binaria contendo as palavras mais frequentes para este arquivo :" << endl << endl;
    cout << "Em ordem :" << endl;
    inordem(binaria);
    cout << endl << "Pre ordem :" << endl;
    preordem(binaria);
    cout << endl << "Pos ordem :" << endl;
    posordem(binaria);
    cout << endl;

    cout <<  endl << "AVL contendo as palavras mais frequentes para este arquivo :" << endl << endl;
    cout << "Em ordem :" << endl;
    inordem(avl);
    cout << endl << "Pre ordem :" << endl;
    preordem(avl);
    cout << endl << "Pos ordem :" << endl;
    posordem(avl);
    cout << endl;
}

void ContarFrequenciaNoTexto(string palavra, string FileName) {
    string linha;
    int frequencia = 0;
    
    ifstream dataFile(FileName);

    if (!dataFile.is_open()) {
        cout << "NAO FOI POSSIVEL ABRIR O ARQUIVO '" << FileName << "' !!! " << endl;
    }

    while (getline(dataFile, linha)) {
        stringstream ss(linha);
        string token;
        
        while (ss >> token) {
            token.erase(remove_if(token.begin(), token.end(), ::ispunct), token.end());
            transform(token.begin(), token.end(), token.begin(), ::tolower);
            token = ConverterAcentuadasParaMinusculas(token);
            
            if (token == palavra) {
                frequencia++; // Incrementa a frequência se a palavra for encontrada no texto.
            }
        }
    }

    cout << endl << "A palavra '" << palavra << "' aparece " << frequencia << " vezes neste texto" << endl;
}

bool CaracterEstranho(string word) { // se o caractere estiver na lista de inválidos, retorne falso
    static unordered_set<char> invalidChars = {static_cast<char>(0xE2), static_cast<char>(0x80), static_cast<char>(0x94)}; // sequencia de bytes do travesao
    
    for (char c : word) {
        if (invalidChars.find(c) != invalidChars.end()) {
            return false; 
        }
    }
    return true;
}

string ConverterAcentuadasParaMinusculas(string num) {
    string maiuscula = "ÁÀÃÉÈÍÌÓÒÚÙ";
    string minuscula = "áàãéèíìóòúù";

    for (size_t i = 0; i < maiuscula.size(); i++) {
        replace(num.begin(), num.end(), maiuscula[i], minuscula[i]);
    }
    return num;
}