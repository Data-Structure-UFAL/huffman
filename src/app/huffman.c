#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "adt.h"
#include "huffman.h"


int main()
{
    int choice = initial_message();
    char path[255];

    puts("Digite o caminho do arquivo\n");
    scanf("%s", path);
  
    switch (choice)
    {
    case 1:
        compress(path);
        break;

    case 2:
        puts("Digita como deve ser salvo o arquivo. Exemplo: 'imagem.png'\n");
        char path_decompress[255];
        scanf("%s", path_decompress);
        decompress("compress.huff", path_decompress);
        break;
    
    default:
        puts("Digite uma escolha válida!");
        break;
    }

    return 0;
}