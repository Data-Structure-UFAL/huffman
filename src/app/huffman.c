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
        Huff_Tree * huff_tree = create_huffman_tree(queue);

        

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