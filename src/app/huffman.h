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

    FILE * file = fopen("compress.huff", "rb"); /* Verificar o porque de quando ler byte a byte ler invertido os 16 bits */

    unsigned short first_16_bits = 0;
    fread(&first_16_bits, sizeof(unsigned short), 1, file);

    fclose(file);

    unsigned short  trash = get_trash(first_16_bits);
    unsigned short  tree_size = get_size_tree(first_16_bits);

    //apagar
    printf("trash %d\n", trash);
    printf("trash size %d\n", tree_size);

    /* Montando dados em preordem */
    unsigned char preorder[tree_size]; /* add \0 ? */
    preorder[tree_size] = '\0';
    for (int i = 0; i < tree_size; i++)
    {
        int current_index_file = i + 2;
        preorder[i] = data->byte[current_index_file];
        
    }
    printf("preorder: %s\n", preorder);

    int index = 0;

    /* construir arvore */
    Huff_Tree * huff_tree = (Huff_Tree *)malloc(sizeof(Huff_Tree));
    huff_tree->root = NULL;

    huff_tree->root = read_pre_order(preorder, &index, huff_tree->root, tree_size);

    //apagar
    print_pre_order(huff_tree->root);

    /* Revisar logica de tratar o lixo */


    int qts_bytes_completos = data->size - 2 - tree_size;
    if(trash) qts_bytes_completos--;

    printf("qtd bytes completo: %d\n", qts_bytes_completos);

    decoding(huff_tree->root, qts_bytes_completos);

}


#endif 