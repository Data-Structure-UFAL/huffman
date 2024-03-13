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
        printf("Comprindo arquivo: %s\n", path);
        
        /* ### PROCESSO DE COMPRESSÃO ### */

        /* Ler arquivo em binário */
        object_data * binary_data= read_initial_file(path);
        printf("\tbyte: %s\n\tsize: %ld\n", binary_data->byte, binary_data->size);

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

        Node * current = queue->head;
        while (current != NULL)
        {
            printf("\tc: %c  -  f: %d\n", current->byte, current->priority );
            current = current->next;
        }
        
        /* Criar arvore de huffman */
        Node * huff_tree = create_huffman_tree(queue);
        printf("altura: %d\n", tree_height(huff_tree));
        print_huff_tree(huff_tree, tree_height(huff_tree));

        /* Montar Dicionário */
        int column = tree_height(huff_tree) + 1;
        char ** dictionary = create_empty_dictionary(column);
        create_dictionary(dictionary, huff_tree, "", column);

        print_dictionary(dictionary);


        char * text_coded = coding_text(dictionary, binary_data->byte);
        printf("\t%s\n", text_coded);

       
        char * text_decoded = decoding_text(text_coded, huff_tree);
        printf("\t%s\n", text_decoded);
        
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