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


        /* int qts_bytes_completos = size_text_coding(dictionary,binary_data);

        decoding(huff_tree, trash_size, qts_bytes_completos); */
               
        decompress("compress.huff", "");
        break;

    case 2:
        printf("Descomprindo arquivo: %s\n", path);
        break;
    
    default:
        puts("Digite uma escolha válida!");
        break;
    }

    return 0;
}