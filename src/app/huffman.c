#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "adt.h"


int main()
{
    int choice = initial_message();
    char path[255];

    puts("Digite o caminho do arquivo\n");
    scanf("%s", path);
  
    switch (choice)
    {
    case 1:

        /* Ler arquivo em binário */
        object_data * binary_data= read_initial_file(path);

        /* Criar lista de frequencia */
        int arr_freq[ASCII_LENGTH];
        get_frequency(binary_data, arr_freq);
        
        /* Cria lista de prioridade */
        Huff_Queue * queue = create_queue();

        for (int i = 0; i < ASCII_LENGTH; i++)
        {
           if(arr_freq[i] > 0){
            Node * new_node = create_node(i, arr_freq[i]);
            enqueue_priority(queue, new_node);
           }
        }
        
        /* Criar arvore de huffman */
        Node * huff_tree = create_huffman_tree(queue);

        /* Montar Dicionário */
        int column = tree_height(huff_tree) + 1;
        char ** dictionary = create_empty_dictionary(column);
        create_dictionary(dictionary, huff_tree, "", column);



        char * text_coded = coding_text(dictionary, binary_data);

        int trashSize = trash_size(dictionary, binary_data);
        int treeSize = size_tree(huff_tree);

        int initial_header =  int_to_binary(trashSize, treeSize);

        int qts_bytes_completos = size_text_coding(dictionary,binary_data);
        coding(text_coded);

        decoding(huff_tree, trash_size, qts_bytes_completos);
               
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