#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "adt.h"

void compress(char * path_file){
    /* Ler arquivo em binário */
    object_data * binary_data= read_initial_file(path_file);

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

    /* Representação do bytes reduzidos */
    char * text_coded = coding_text(dictionary, binary_data);

    /* Formatação do Header */
    int trashSize = trash_size(dictionary, binary_data);
    int treeSize = size_tree(huff_tree);
    unsigned short initial_header =  int_to_binary(trashSize, treeSize);
    printf("header: %d\n", initial_header);

    char preorder[treeSize];
    int index = 0;
    pre_order_tree(huff_tree, preorder, &index);
    
    write_header(initial_header, preorder, treeSize);

    create_file_compressed(text_coded);
}


void decompress(char * file_compressed_path, char * file_decompressed_path){
    object_data * data = read_initial_file(file_compressed_path);

    /* ler header (Extrair Numero do Lixo e o Size da arvore) */

    FILE * file = fopen("compress.huff", "rb"); /* !!! REVER ESSE MODO DE LER OS 16 PRIMEIROS BITS */

    short first_16_bits = 0;
    fread(&first_16_bits, sizeof(short), 1, file);

    fclose(file);

    /* printf("header readed : int %d", first_16_bits); */

    printf("Numero de bytes: %ld\n", data->size);
    for (int i = 2; i < data->size; i++)
    {
        printf("readed: %c\n", data->byte);
    }
    
    
    /* construir arvore */


    /* int qts_bytes_completos = size_text_coding(dictionary,binary_data); */
    /*  decoding(huff_tree, trash_size, qts_bytes_completos) */

}


#endif 