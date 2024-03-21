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

    - 
3. Criação de uma Priority Queue
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
