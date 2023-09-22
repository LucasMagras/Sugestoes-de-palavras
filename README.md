# Sugestoes-de-palavras

## Problema proposto
<p align="justify">
Neste trabalho, o objetivo foi criar um sistema que possibilite a funcionalidade de autocompletar e oferecer sugestões de palavras aos usuários. Para atingir essa finalidade, foi adotado a estrutura da árvore binária como base. Ao iniciar o codigo, é lido um arquivo denominado input.data, contendo uma lista de palavras. Cada palavra nesse arquivo é considerada como termo de pesquisa para o sistema. Foi utilizado um conjunto de árvores binárias para construir o sistema. Essas árvores foram criadas a partir de textos previamente fornecidos (disponíveis na pasta dataset). O objetivo é estabelecer uma relação entre as palavras dos textos e as palavras de pesquisa. Para cada palavra no arquivo input.txt, é percorrido as árvores binárias para identificar a palavras mais relevantes e próximas à palavra de pesquisa. Foram priorizadas as palavras frequentes e associadas ao termo de pesquisa.

## Lógica implementada
<p align="justify">
Para resolver esse problema assim como no trabalho anterior (Top-K-elementos), foi utilizado a hash para contar a frequência de todos os itens, enquanto o heap se aplica na manutenção de uma lista dos k itens de maior valor. Para implementar a tabela hash foi usada a biblioteca <i>unordered_map</i> que permite criar uma hash com mais facilidade. Para implementar a heap foi usada a biblioteca <i>queue</i> utilizando a priority_queue como estrutura. Por fim foi usado uma struct <i>Item</i> para armazenar uma palavra e sua frequencia. Essa frequencia será utilizada depois para montar as árvores binarias, que serão construidas apenas se alguma palavra do arquivo 'input.txt' for encontrada no texto que está sendo analisado. Caso alguma palavra seja encontrada, são montada as 3 árvores : Árovre binária, AVL e a Árvore de Huffman contendo as palavras mais frequentes que estão armazenadas na heap. Os resultados da análise são apresentados em um arquivo chamado output.txt. Esse arquivo contém as relações entre as palavras pesquisadas e cada arquivo de texto. Além disso, a relevância de cada palavra é calculada com base em sua frequência nos textos. Para tal, foi utilizado o trabalho recentemente realizado, o contador de palavras.

### Hash
<p align="justify">
Como foi dito, para implementar a tabela hash foi usado a estrutura <i>unordered_map</i> que é uma classe de contêiner da biblioteca padrão do C++. Esse tipo de estrutura é usado para armazenar pares de chave-valor, onde cada chave é única e mapeia para um valor correspondente. O <i>unordered_set</i> oferece acesso rápido aos valores com base em suas chaves. Neste caso as chaves são do tipo string (representando as palavras) e os valores são do tipo int (representando as frequências das palavras).  Se a palavra já estiver presente na tabela, sua frequência é incrementada. Se não estiver presente, uma nova entrada é criada com frequência 1.

<p align="justify">
Como em qualquer tabela de dispersão, pode ocorrer colisões quando duas chaves diferentes geram o mesmo valor de hash. As técnicas para lidar com colisões variam, mas a biblioteca padrão do C++ geralmente utiliza o método de "encadeamento" para resolver essas situações. No método de encadeamento, cada posição da tabela de dispersão contém uma lista ligada de elementos que possuem o mesmo valor de hash. Quando ocorre uma colisão, um novo elemento é simplesmente adicionado à lista ligada correspondente. O encadeamento é uma técnica eficaz para lidar com colisões, mas ele pode causar aumento no uso de memória devido à necessidade de armazenar as listas ligadas. No entanto, essa abordagem oferece um bom desempenho médio para inserção, busca e remoção de elementos, tornando o unordered_map uma estrutura de dados poderosa e versátil para lidar com mapeamentos de chave-valor. 

### Heap
<p align="justify">
Uma heap é uma estrutura de dados fundamental que organiza um conjunto de elementos de forma hierárquica, de modo que o elemento pai tenha um valor maior ou menor (dependendo do tipo de heap) do que seus filhos. A heap é frequentemente usada para implementar filas de prioridade, onde os elementos são acessados com base em sua prioridade relativa, o que foi o caso deste trabalho, já que foi usada uma priority_queue que usa uma heap como sua estrutura de armazenamento subjacente. Essa heap garante que os elementos sejam organizados de acordo com a prioridade, com o elemento de maior (ou menor) prioridade no topo. No contexto do código, a heap foi usada para manter os "k" elementos mais valiosos (mais frequentes) durante o processo de contagem de frequência das palavras. Isso permitiu que fosse identificado rapidamente os elementos mais valiosos em termos de frequência à medida que processa as palavras do texto.

### Árvore Binária
<p align="justify">
Uma árvore binária é uma estrutura de dados em que cada nó pode ter até dois filhos, conhecidos como filho esquerdo e filho direito. A estrutura de uma árvore binária é composta por nós, onde cada nó pode conter algum dado ou valor, e esses nós são organizados hierarquicamente de forma que um nó pai pode ter no máximo dois filhos. Quando um nó não possui filhos, ou seja, seus ponteiros de filho esquerdo e direito estão livres ou com valores como NULL, chamados esse nó de folha e consideramos que este tipo de nó delimita o "fundo" da estrutura. A Fig. 1 detalha em alto nível esse modelo de estrutura de dados em detalhes.

<p align="center">
<img src="img/binary.png"/> 
</p>

<p align="center"> Fig 1. Exemplo de árvore binaria. </p>

<p align="justify">
A partir da Fig. 1 é possível observar algumas características importantes da estrutra em árvore. Primeiro, a estrutura detalha sua altura computando os níveis de hierarquia. No exemplo, é possível observar que, partindo do nó raiz (i.e., 5), temos como altura da árvore 3, considerando que a raiz se encontra em nível zero. Assim, identificar a altura de uma estrutura em árvore é equivalente a econtrar, partindo-se da raiz, o nó folha mais profundo existente. Observe na Fig. 1, que todo nó da estrutura apresenta no máximo dois filhos. Isso caracteriza a estrutura como binária, cujos nós são, no máximo, de grau 2. Consideramos como grau a quantidade de ponteiros conectados em um determinado nó.
<p align="justify">
Por fim, ainda utilizando da representação da Fig. 1, podemos observar que é possível identificar a altura da estrutura. Em literatura, uma árvore binária balanceada apresenta como altura o fator de logn, com n representando o número de elementos inseridos. Esse balanceamento é obtido mantendo-se todas as folhas em níveis muito próximos, sendo aceitável uma variação de no máximo 1 de altura para variações. Consideramos esse contexto como caso médio, isso se considerarmos que as inserções são sempre realizadas a partir de valores aleatórios não ordenados. Caso contrário, se valores ordenados forem utilizados tem-se a possibilidade da altura ser linear em relação ao tamanho da entrada. Nesse último caso, a estrutura passará a apresentar ligações muito semelhantes a uma lista simplesmente encadeada e seus custos passam a acompanhar os já apresentados nesta estrutura.
<p align="justify">
Para este projeto o nó da árvore binaria foi feito com uma struct que contém a palavra, sua frequência e os ponteiros right e left que representam os filhos esquerdo e direito de um nó na árvore binária, além de um construtor que é usado para criar um novo objeto Binaria. Ele aceita dois argumentos: uma palavra (como uma string) e uma frequência (como um inteiro). Quando um novo nó é criado, esse construtor é usado para inicializar os valores dos membros word e frequency, enquanto left e right são inicializados como ponteiros nulos (nullptr).

#### Função insert
<p align="justify"> 
Para inserir os elementos na árvore binaria foi cirada a função 'insert' que é uma função recursiva que insere um novo nó na árvore. A função recebe 3 argumentos, Binaria* root que é um ponteiro para a raiz da árvore, string word que é a palavra que será inserida e int frequency que é a frequência desta palavra. Primeiro, a função verifica se o nó raiz (root) é nulo. Se for nulo, isso significa que a árvore está vazia ou que foi alcançada uma folha da árvore onde um novo nó pode ser inserido. Nesse caso, a função cria um novo nó Binaria com os valores word e frequency passados como argumentos e retorna um ponteiro para esse novo nó, efetivamente adicionando-o à árvore. Se o nó raiz não for nulo, a função verifica se a frequency do novo nó é menor do que a frequency do nó atual (root). Se for menor, isso significa que o novo nó deve ser inserido à esquerda do nó atual. A função chama recursivamente a função insert no filho esquerdo (root->left) e atualiza o filho esquerdo do nó atual com o resultado dessa chamada.Se a frequency do novo nó for maior do que a frequency do nó atual, a função chama recursivamente a função insert no filho direito (root->right) e atualiza o filho direito do nó atual com o resultado dessa chamada. Se a frequency do novo nó for igual à frequency do nó atual, isso significa que a palavra já existe na árvore com a mesma frequência. Nesse caso, a palavra é adicionada ao vetor palavras do nó atual.
<p align="justify"> 
Finalmente, a função retorna o nó atual (ou o novo nó criado no caso da raiz ser nula ou o nó original com atualizações) após a inserção. A função garante que o nós são organizados de forma que os valores menores estão à esquerda e os valores maiores estão à direita, garantindo que a árvore seja ordenada de acordo com o critério de frequência. Vale ressaltar que como a inserção na arvore binaria é feita pegando os elementos da heap que está ordenada de acordo com a frequência, a função 'insert' acaba
inserindo todos os elementos na sub-árvore da direita (já que os elementos da heap estão em ordem crescente), o que gera um desbalanceamento na árvore tranformando ela em uma lista linear. Esse problema é resolvido na próxima estrutura usada, a árvore AVL, por isso resolvi deixar desta forma.

> Vale ressaltar que os elementos que são inseridos na árvore são os elementos que estão na heap que contém as palarvas mais frequentes do texto. Essa heap está ordenada, ou seja, a função 'insert' irá inserir todos os nós na sub-arvore da direita (já que a heap esta ordenada de forma crescente), gerando um desbalanceamento e transformando a árvore em uma lista linear. Este problema é resolvido na próxima estrutura, a árvore AVL, por isso deixei desta forma.

### AVL
<p align="justify"> 
Uma árvore AVL é uma estrutura de dados de árvore binária balanceada que foi projetada para manter o equilíbrio automático durante operações de inserção e remoção. O equilíbrio de uma árvore AVL é uma propriedade importante que garante que a altura das subárvores esquerda e direita de qualquer nó seja no máximo 1. Isso resulta em um desempenho de busca eficiente, com uma complexidade de tempo logarítmica em relação ao número de nós. Para a realização dos balanceamentos, a AVL modifica o método de inserção da árvore binária, introduzindo nela um procedimento de avaliação de peso e quatro modelos de rotação. O fator de peso é utilizado para identificar quando a árvore se apresenta desbalanceada, para com isso identificar que tipo de rotação é preciso empregar na estrutura para que essa volta e se manter aproximadamente balanceada. A abordagem do fator de peso pode ser observada através da Fig 2.

<p align="center">
<img src="img/avl.png"/> 
</p>

<p align="center"> Fig 2. Exemplo de árvore AVL. </p>

<p align="justify"> 
Observe, por meio da representação da Fig 2, que os fatores de peso podem se apresentar entre -1 e +1. Isso demonstra que a árvore em questão está balanceada segundo suas regras. Para obter esse fator de peso, consideramos a avaliação do nível de altura do filho mais profundo de cada sub-árvore (i.e., esquerda e direita). Quando uma sub-árvore esquerda é avaliada, seu valor de peso se apresenta como negativo. Pelo contrário, quando a sub-árvore direita é observada, essa leva para os níveis mais acima valores positivos de altura. Então, uma árvore AVL se encontra desbalanceada se o fator de peso de um dado nó excede o limiar entre -1 e +1. Neste caso, as rotações são realizadas para retornar a estrutura à condições aceitáveis.
<p align="justify"> 
Em uma árvore AVL desbalanceada, um total de 4 rotações podem ser realizadas, duas simples e duas duplas. Considera-se rotações simples esquerda e/ou direita a movimentação da estrutura em um único processo. Essas são aplicadas sempre que o fator de peso do nó desbalanceado coincidir em sinal com a sub-árvore que levou ao desbalanceamento. Observe abaixo na Fig 3 um exemplo de rotação simples para direita. Neste, note que o sinal dos fatores de peso do nó que gerou o desbalanceamento (i.e., nó 8) e da sub-árvore causadora do mesmo (i.e., 4) são iguais. Isso caracteriza uma rotação simples para direita, uma vez que ambos os sinais são negativos, o que indica que o desbalanceamento gerado está na esquerda.

<p align="center">
<img src="img/rsd.png"/> 
</p>

<p align="center"> Fig 3. Exemplo de rotação à direita para rebalanceameto da árvore binária. </p>

<p align="justify"> 
Considerando ainda o exemplo da Fig 3, observe que ao produzir o rebalanceamento necessário, neste caso, obtivemos duas grandes modificações. Primeiro, como o desbalanceamento ocorreu na raiz da árvore, essa sofreu modificação, deixando de ser o nó 8 para se tornar o nó 4. Segundo, o filho direito de 4, representado pelo nó 6, deixa de conectar a ele para se tornar o filho esquerdo do nó 8. Esse segundo passo é necessário para garantir a integridade das regras básicas de uma árvore binária, a qual define a existência de apenas um filho na esquerda e um como filho direito. Então, ao imaginar a rotação é preciso observar essas peculiaridades para não errar a recomposição da estrutura. Vejamos agora como proceder sob modelos de rotação dupla. A Fig 4 detalha um exemplo para este caso.

<p align="center">
<img src="img/rdd.png"/> 
</p>

<p align="center"> Fig 4. Exemplo de rotação dupla à direita para rebalanceameto da árvore binária. </p>

<p align="justify"> 
Em uma rotação dupla, conforme pode ser observado na Fig 3, dois movimentos são necessários. Para detecnar a necessidade desses movimentos, basta observar o sinal atribuído ao fator de do nó desbalanceado e o da sub-árvore causadora do problema. Note que, o nó desbalanceado mais uma vez é o nó cujo valor é 8. Nesse nó temos um fator de peso de -2, o que indica um desbalanceamento de sua sub-árvore esquerda. Já em sua sub-árvore esquerda observamos um fator de peso positivo, o que indica a necessidade de rotação dupla para correção. Neste caso, primeiramente produzimos uma rotação simples na sub-árvore esquerda para igualar seu sinal de fator de peso ao sinal do nó desbalanceado. Feito isso, produzimos uma segunda rotação ao contrário para corrigir o nó sinalizado no início como desbalanceado. Note que ao produzir rotações nos filhos, valores maiores que 1 podem ser produzidos, como no caso do nó 6 que recebeu após rotação um fator de -2. Embora saibamos que esse valor indica desbalanceamento, este é ignorado, uma vez que, tal fator só foi produzido após rotação de correção. Além disso, observe que para alinhar corretamente a estrutura, os nós de valor 5 e 6 foram realinhados. Isso é preciso porque ao realizar a rotação sem o realinhamento a composição da árvore ficará errada, tendo como filho direito do nó 6 o nó cujo valor é 5. Então, ao detectar uma rotação dupla, observe se o primeiro giro fará com que a integridade da estrutura se mantenha. Caso contrário, faça primeiro o alinhamento conforme demonstrado no exemplo, depois gire a estrutura.

#### Função insert
<p align="justify"> 
Para inserir os elementos na AAVL foi criada a função 'insert' que recebe 3 argumentos, 'AVL* root' que é um ponteiro para a raiz da árvore AVL, string word que é a palavra que será inserida e int frequency que é a frequência desta palavra. Primeiro, a função verifica se o nó raiz (root) é nulo. Se for nulo, isso significa que a árvore está vazia ou que foi alcançada uma folha da árvore onde um novo nó pode ser inserido. Nesse caso, a função cria um novo nó AVL com os valores word e frequency passados como argumentos e retorna um ponteiro para esse novo nó. Se o nó raiz não for nulo, a função compara a frequency do novo nó com a frequency do nó atual (root). Com base nessa comparação, a função decide se o novo nó deve ser inserido na subárvore esquerda ou direita do nó atual. Após a inserção do novo nó, a altura do nó atual (root) é atualizada com base na altura máxima entre suas subárvores esquerda e direita. A função calcula o fator de equilíbrio do nó atual chamando a função getBalanceFactor(root). O fator de equilíbrio é a diferença entre as alturas da subárvore esquerda e da subárvore direita. A função verifica se ocorreu um desequilíbrio na árvore. Se o fator de equilíbrio for maior que 1, isso indica um desequilíbrio na subárvore esquerda. Dependendo da relação entre a frequency do novo nó e a frequency do filho esquerdo do nó atual, são realizadas rotações para restaurar o equilíbrio. Da mesma forma, se o fator de equilíbrio for menor que -1, isso indica um desequilíbrio na subárvore direita, e novamente são realizadas rotações apropriadas. A função retorna o nó atual (ou o novo nó criado no caso da raiz ser nula ou o nó original com atualizações) após a inserção e o balanceamento.

#### Função getHeight
<p align="justify"> 
Esta função calcula a altura de um nó na árvore AVL. Ela recebe um nó (AVL* node) como argumento e retorna a altura desse nó. Se o nó for nulo (representando uma subárvore vazia), a altura é considerada como 0.

#### Função getBalanceFactor
<p align="justify"> 
Esta função calcula o fator de equilíbrio de um nó na árvore AVL. O fator de equilíbrio é a diferença entre as alturas da subárvore esquerda e da subárvore direita do nó. Se o nó for nulo, o fator de equilíbrio é considerado como 0.

#### Função rightRotate
<p align="justify"> 
Esta função realiza uma rotação simples para a direita em torno do nó y na árvore. Ela recebe o nó y como argumento e retorna o novo nó que se tornará a raiz da subárvore que antes tinha y como raiz. Um novo nó x é criado e recebe o filho esquerdo de y como seu filho direito. Isso significa que x "herda" o filho esquerdo de y. O filho esquerdo de y (x->right) agora se torna o filho esquerdo de y. Portanto, y perde seu filho esquerdo. Em seguida, as alturas de y e x são atualizadas. A altura de y é recalculada como a altura máxima entre suas novas subárvores esquerda e direita mais 1. A altura de x também é recalculada da mesma maneira. Finalmente, a função retorna o novo nó x, que agora é a raiz da subárvore onde a rotação ocorreu.

#### Função leftRotate
<p align="justify"> 
Esta função realiza uma rotação simples para a esquerda em torno do nó x na árvore. Ela recebe o nó x como argumento e retorna o novo nó que se tornará a raiz da subárvore que antes tinha x como raiz. Um novo nó y é criado e recebe o filho direito de x como seu filho esquerdo. Isso significa que y "herda" o filho direito de x. O filho direito de x (y->left) agora se torna o filho direito de x. Portanto, x perde seu filho direito. Em seguida, as alturas de x e y são atualizadas. A altura de x é recalculada como a altura máxima entre suas novas subárvores esquerda e direita mais 1. A altura de y também é recalculada da mesma maneira. Finalmente, a função retorna o novo nó y, que agora é a raiz da subárvore onde a rotação ocorreu.

### Árvore de Huffman

### Estrutura do codigo
<p align="justify">

### Tratamentos
<p align="justify">
Antes de cada palavra ser inserida, ela passa alguns tratamentos, sendo um para remover os sinais de pontuação, dois para transformar todas as letras maiusculas para minusculas e um para tratar caracteres estranhos, além de um para tratar caracteres estranho. Para usar esses tratamentos foi necessario incluir a biblioteca <i>algorithm</i>. Para remover os sinais de pontuação foi usada a função erase junto com as funções remove_if, que remove elementos de uma sequência que atendem a uma determinada condição e a função ispunct que é usada para determinar se um caractere é um caractere de pontuação (por exemplo, vírgula, ponto, ponto-e-vírgula). A função remove_if remove os caracteres que atendem à condição passada, neste caso, ispunct, que verifica se um caractere é um sinal de pontuação.
 
```cpp
token.erase(remove_if(token.begin(), token.end(), ::ispunct), token.end());  // remove sinais de pontuação do token
```
 
<p align="justify">
Já a função transform é usada para aplicar uma transformação a cada elemento em uma sequência (como um vetor, uma string, etc.) e armazenar os resultados em outra sequência ou na mesma sequência. No caso deste codigo, ela esta sendo usada para converter todos os caracteres do token para letras minúsculas, usando a função tolower como argumento. Essa transformação garante que palavras com diferentes caixas (maiúsculas/minúsculas) sejam tratadas como iguais. 
 
```cpp
transform(token.begin(), token.end(), token.begin(), ::tolower); // transforma para letras minusculas
```
Além disso foi criada a função ConverterAcentuadasParaMinusculas() que trata apenas os caracteres acentuados, transformando todos em minusculos, já que a conversão de caracteres acentuados entre maiúsculas e minúsculas nem sempre é direta devido às diferenças entre os conjuntos de caracteres ASCII e Unicode, além da que a forma de representar um caracter acentuado é diferente de uma representação de um caracter normal. Essa função recebe uma string como argumento e duas strings são definidas, maiuscula e minuscula, cada uma delas contém caracteres acentuados maiúsculos e seus equivalentes minúsculos, respectivamente. O loop percorre os caracteres da string maiuscula, e a função replace é usada para substituir todas as ocorrências do caractere acentuado maiúsculo pelo seu equivalente minúsculo na string que a função recebeu. Isso é feito para cada caractere acentuado na sequência maiuscula. Após o loop a função retorna a string com os caracteres acentuados minusculos.

```cpp
string ConverterAcentuadasParaMinusculas(string num) {
    string maiuscula = "ÁÀÃÉÈÍÌÓÒÚÙ";
    string minuscula = "áàãéèíìóòúù";

    for (size_t i = 0; i < maiuscula.size(); i++) {
        replace(num.begin(), num.end(), maiuscula[i], minuscula[i]);
    }
    return num;
}
```
<p align="justify">
Ainda existe outra função criada no código para tratar apenas de um caracter em espedifico, neste caso o travessão. A função que remove todos os sinais de pontuação não consegue remover o travessão, porque o caractere '—' é um caractere especial e pode ter representações diferentes dependendo da codificação do arquivo. Para tratar isso foi usada a sequencia de bytes que representa o caractere '—' na codificação UTF-8, que se for achada na hash usando a função find(), retornará false.
 
```cpp
bool CaracterEstranho(string word) { // se o caractere estiver na lista de inválidos, retorne falso
    static unordered_set<char> invalidChars = {static_cast<char>(0xE2), static_cast<char>(0x80), static_cast<char>(0x94)}; // sequencia de bytes do travessao
    
    for (char c : word) {
        if (invalidChars.find(c) != invalidChars.end()) {
            return false; 
        }
    }
    return true;
}
```

## Resultado

## Conclusão
<p align="justify">
Ao concluir este trabalho, obtivemos uma compreensão mais aprofundada das diferentes implementações das árvores binárias e sua influência no sistema de autocompletar e sugestões de palavras. A análise comparativa nos permite avaliar a eficácia de cada abordagem em termos de desempenho e funcionalidade.

 
## Compilação e Execução

Esse pequeno exemplo possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |
