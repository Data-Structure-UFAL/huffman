# Algoritimo de Huffman

## Objetivo

## Arquitetura do Projeto

## Fluxo do Huffman

### Compactar 

1. Leitura do Arquivo 
    - Para a leitura dos arquivos, foi usado a leitura do arquivo em modo binário, com isso foi possível mapear todos os bytes que formam o arquivo em específico, seja ele texo, imagem, vídeo ...
    
    - O struct OBJECT_DATA armazena os bits e a quantidade de bytes

    - A função read_initial_file(path_file) é responsável por fazer a leitura do arquivo, armazenar os dados referentes as OBJECT_DATA

2. Mapeamendo da Frequência de Bytes 

    - A função get_frequency(object_data * data, int arr_frequency[]) em _utils.h_ recebe o arquivo em binário e um array com o tamanho de caracteres ASCII. O array é inicializado com 0 e, durante o loop (que percorre de 0 até o tamanho do arquivo em bytes), é incrementando +1 na posição com índice que corresponde àquele byte.
3. Criação de uma Priority Queue
    - Na função compress em _huffman.h_, uma fila de prioridade é inicializada e há um loop que percorre de 0 até o tamanho da tabela ASCII. A cada iteração, verificamos se o valor no índice i no array de frequência é maior que 0. Um novo nó é criado passando o índice i (byte) e sua frequência. Por fim, enfileiramos os bytes sempre inserindo o de menor frequência na head da fila.
4. Criar Árvore de Huffman
5. Montar Dicionário
6. Representação dos Bits Comprimidos
7. Formação do Header 
8. Escrever Dados no Arquivo Compactado

### Descompactar 
1. Leitura do Arquivo Compactado
2. Extrair Informações do Header 
3. Construir Árvore de Huffman (A partir dela em pre-ordem)
4. Escrever Dados no Arquivo Descompactado
