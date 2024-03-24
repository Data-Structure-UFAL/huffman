#ifndef ADT_H
#define ADT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define ASCII_LENGTH 256

typedef struct node
{
    void *byte;
    void *priority;
    struct node *next;
    struct node *left;
    struct node *right;
} Node;

typedef struct
{
    Node *head;
    int size;
} Huff_Queue;

typedef struct
{
    Node *root;
} Huff_Tree;

/*
    - OBJETIVO: Criar um nó
    - PARAMETRO: É passado dois parâmetros, um informando o byte e outro a frequência daquele byte
    - RETORNO: É retornado um nó com as informações passadas
*/
Node * create_node(void *byte, void *frequency);

/*
    - OBJETIVO: Criar uma lista 
    - PARAMETRO: Não tem parâmetro
    - RETORNO: É retornado o head da lista apontando para NULL
*/
Huff_Queue * create_queue();

/*
    - OBJETIVO: Verificar se a lista de prioridade está vazia
    - PARAMETRO: É passado um ponteiro para a lista de prioridade
    - RETORNO: É retornado 1 se a lista estiver vazia e 0 caso contrário
*/
int is_empty_queue(Huff_Queue * queue);

/*
    - OBJETIVO: Adicionar de forma ordenada um novo nó na lista de prioridade
    - PARAMETRO: É passado um ponteiro para a lista de prioridade, e  o nó que deve ser adicionado
    - RETORNO: Não é retornado nada, mas é adicionado um novo node na lista de prioridade
*/
void enqueue_priority(Huff_Queue * queue, Node * new_node);

/*
    - OBJETIVO: Remover o head de uma Lista
    - PARAMETRO: É passado a Lista como parâmetro
    - RETORNO: É retornado o nó removido
*/

Node * dequeue(Huff_Queue * queue);

/*
    - OBJETIVO: Criar uma árvore de huffman
    - PARAMETRO: É passado a Lista como parâmetro
    - RETORNO: É retornado um nó representando o a Raiz da arvore montada
*/
Node * create_huffman_tree(Huff_Queue * queue);

/* 
- Objetivo: Calcular a altura da arvore
- Parametro: Um no apontando para a raiz da arvore
- Retorno: Um inteiro representando a altura
*/
int tree_height(Node * root);

/* 
- Objetivo: Fazer alocação de memória do dicionário
- Parametro: Um inteiro representando o numero de colunas
- Retorno: Um ponteiro que aponta para um array de strings
*/
char ** create_empty_dictionary(int column);

/* 
- Objetivo: Criar um dicionário que referencia o caminho das folhas de um byte 
    de forma recursiva.
- Parametro: Dicionario Alocado, Raiz, Caminho Vazio, Numero de Colunas
- Retorno: Sem retorno... altera o dicionário por referencia
*/
void create_dictionary(char **dictionary, Node *root, char *path, int column);

/* 
- Objetivo: Calcular o numero de bits com referencia ao dicionario
- Parametro: Dicionario, Texto
- Retorno: Um inteiro representando o numero de bits
*/
int size_text_coding(char ** dictionary, object_data * data);

/* 
- Objetivo: Codificar um texto em bits (formato de texto) com base no dicionario
- Parametro: Dicionario, Texto
- Retorno: Uma string de um texto codificado
*/
char *coding_text(char **dictionary, object_data *data);

/*
	-Objetivo: Calcular o tamanho do lixo, ou seja, os bits restantes para completar um byte
	-Parâmetro: Dicionário, Texo Codificado
	-Um inteiro representando o tamanho do lixo
*/
int trash_size(char ** dictionary, object_data * data);

/*
	-Objetivo: Calcular o numero de nodos que serão gravados no header em preordem, ou seja, os nods da arvore + caracter de escape caso necessário
	-Parâmetro: Um nó representado a raiz da arvore
	-Retorno: Um inteiro representando o numero de 
*/
int size_tree(Node * node);



/*
	-Objetivo: Gravar os bits do header em uma variável de 16 bits
	-Parâmetro: Dois inteiros representando o lixo e o numero de nodos
	-Retorno: Um unsigned short (16 bits) representando o inicio do header
*/
unsigned short int_to_binary(int trash, int size_tree);


/*
	-Objetivo: Criar um arquivo com os bytes codificados
	-Parâmetro: Texto codificado
	-Retorno: Sem retorno, apenas um arquivo é criado representando o arquivo comprimido
*/
void create_file_compressed(char * text_coded);

/*
	-Objetivo: Criar um arquivo com os dados descomprimidos
	-Parâmetro: Um nodo para a raiz, Quantia de bytes completos, o numero de nodes, o tamanho do lixo
	-Retorno: Sem retorno, apenas cria um arquivo descomprimido
*/
void decoding(Node *root, int qts_bytes_completos, int treeSize, int trashSize);


/*
	-Objetivo: Gravar a arvore em pre ordem em uma variável local
	-Parâmetro: Raiz, Uma string por referência, index por referencia
	-Retorno: Sem retorno, a funcao modifica uma variável por referência
*/
void pre_order_tree(Node * root, char * preorder, int *index);

/*
	-Objetivo: Criar uma arvore a partir de dados em pre-ordem
	-Parâmetre: Arvore em preordem, ponteiro para o index, Nodo para a raiz, o numero de nodos
	-Retorno: Uma nodo apontando para a raiz da arvore
*/
Node *construt_tree_preorder_data(unsigned char *tree, int *index, Node *arvore, int size);



Node * create_node(void *byte, void *frequency){
    Node *new_node = malloc(sizeof(Node));

    int *priority = (int *) malloc (sizeof(int));
    *priority = *(int *) frequency;

    unsigned char *new_byte = (unsigned char *)malloc(sizeof(unsigned char));
    *new_byte = *(unsigned char *)byte;

	new_node->priority = priority;
    new_node->byte = new_byte;
    new_node->left = NULL; 
    new_node->right = NULL; 
    return new_node;
}


Huff_Queue * create_queue(){
    Huff_Queue * new_queue = malloc(sizeof(Huff_Queue));
    new_queue->head = NULL;
    new_queue->size = 0;
    return new_queue;
}


int is_empty_queue(Huff_Queue * queue){
    return queue->head == NULL;
}


void enqueue_priority(Huff_Queue * queue, Node * new_node){
   /*  Node * new_node = create_node(byte, freq); */

    if(is_empty_queue(queue) || (*(int *)new_node->priority <= *(int *)queue->head->priority)){
        new_node->next = queue->head;
        queue->head = new_node;
        queue->size++;
        return;
    } 

    Node * current = queue->head;

    while (current->next != NULL && (*(int *)new_node->priority > *(int *)current->next->priority)){
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node; /* verificar isso aqui dps */
    queue->size++;
}

Node * dequeue(Huff_Queue * queue){
    if(is_empty_queue(queue)){
        printf("Queue Underflow\n");
        abort();
    }

    Node * dequeued = queue->head;

    queue->head = queue->head->next;
    dequeued->next = NULL;

    queue->size--;

    return dequeued;
}

Node * create_huffman_tree(Huff_Queue * queue){
    Node *left, *right, *new_node;

    while (queue->size > 1)
    {
        left = dequeue(queue);
        right = dequeue(queue);

        unsigned char asterisco = '*';
        int sum_priority = *(int *)left->priority + *(int *)right->priority;

        new_node = create_node(&asterisco, &sum_priority); // Allocate memory for the new node
        new_node->left = left;
        new_node->right = right;
        enqueue_priority(queue, new_node);
        
    }

    return dequeue(queue);
}


int tree_height(Node * root){
    int left, right;

    if(root == NULL) return - 1;

    left = tree_height(root->left);
    right = tree_height(root->right);

    return (left > right) ? left + 1: right + 1; 
}

char ** create_empty_dictionary(int column){ /* Remember to use CONST LENGTH_ASCII and not 256*/
    char **dictionary;
    dictionary = malloc(sizeof(char*) * 256); 

    for (int i = 0; i < 256; i++)
        dictionary[i] =  calloc(column, sizeof(char));

    return dictionary;
}

void create_dictionary(char **dictionary, Node *root, char *path, int column) {
    char left[column], right[column];

    if (root->left == NULL && root->right == NULL) {
        strcpy(dictionary[*(unsigned char *)root->byte], path);
    } else {
        //strcpy copia
        strcpy(left, path);
        strcpy(right, path);

        //strcat concatena
        strcat(left, "0");
        strcat(right, "1");

        create_dictionary(dictionary, root->left, left, column);
        create_dictionary(dictionary, root->right, right, column);
    }
}

int size_text_coding(char ** dictionary, object_data * data){
    int length = 0, i = 0;

    for (int i = 0; i < data->size; i++)
    {
        length += strlen(dictionary[data->byte[i]]);
    }
    
    return length;
}

char *coding_text(char **dictionary, object_data *data) {
    int size = size_text_coding(dictionary, data) + 1;
    char *code = calloc(size, sizeof(char));
    char *dest = code;

    for (int i = 0; i < data->size; i++) {
        dest = strcpy(dest, dictionary[data->byte[i]]);
        dest += strlen(dictionary[data->byte[i]]);
    }

    return code;
}



int trash_size(char ** dictionary, object_data * data){
    return 8 - (size_text_coding(dictionary, data) % 8);
}

int size_tree(Node * node){
    if(node == NULL){
        return 0;
    }
 
    if(node->left == NULL && node->right == NULL && (*(unsigned char *)node->byte == '*' || *(unsigned char *)node->byte == '\\')) {
        return 2;
    }

    return size_tree(node->left) + size_tree(node->right) + 1;
}

unsigned short int_to_binary(int trash, int size_tree) {
    unsigned short first_16_bits = 0;

    for (int i = 2; i >= 0; i--)
    {
        int mask = 1 << i;
        if(trash & mask){
            first_16_bits = first_16_bits | (1u << i);
        }
    }

    first_16_bits = first_16_bits << 13;

    for (int i = 12; i >= 0; i--)
    {
        int mask = 1 << i;
        if(size_tree & mask){
            first_16_bits = first_16_bits | (1u << i);
        }
    }

    return first_16_bits; 
}

/* CODING IN ARCHIVE */
void create_file_compressed(char * text_coded){
    FILE * file = fopen("compress.huff", "ab");

    if(!file){
        printf("Problema ao abrir arquivo em Coding()\n");
        return;
    }

    int i = 0, j = 7;
    unsigned char mask, byte = 0;

    while (text_coded[i] != '\0')
    {
        mask = 1;
        if(text_coded[i] == '1'){
            mask = mask << j;
            byte = byte | mask;
        }
        j--;

        if(j < 0){
            fwrite(&byte, sizeof(unsigned char), 1, file);
            byte = 0;
            j = 7;
        }
        i++;
    }
    
    if(j != 7) fwrite(&byte, sizeof(unsigned char), 1, file);


    fclose(file);
}

unsigned int is_on_bit(unsigned char byte, int i){
    unsigned char mask = (1 <<i);
    return byte & mask;
}


void decoding(Node *root, int qts_bytes_completos, int treeSize, int trashSize) {
    FILE *compress_file = fopen("compress.huff", "rb");

    if (!compress_file) {
        printf("Problema ao abrir arquivo em compress_file\n");
        return;
    }

    FILE *decompress_file = fopen("decompress.jpeg", "wb");
    if (!decompress_file) {
        printf("Problema ao abrir arquivo em decompress_file\n");
        fclose(compress_file); // Fechar o arquivo se não puder abrir o outro
        return;
    }

    unsigned char byte;
    Node *current = root;

    fseek(compress_file, treeSize + 2, SEEK_CUR);
    int no_trash = 8 - trashSize;

    while (fread(&byte, sizeof(unsigned char), 1, compress_file)) {
        for (int i = 7; i >= 0; i--) {
            if (qts_bytes_completos == 0 && no_trash == 0) break;

            current = (is_on_bit(byte, i)) ? current->right : current->left;

            if (qts_bytes_completos == 0 && no_trash > 0) no_trash--;

            if (current->left == NULL && current->right == NULL) {
                fwrite(current->byte, sizeof(unsigned char), 1, decompress_file); 
                current = root;
            }
        }

        qts_bytes_completos--; 

        if (qts_bytes_completos == 0 && no_trash == 0) break;
    }

    fclose(compress_file);
    fclose(decompress_file);
}

void pre_order_tree(Node * root, char * preorder, int *index)
{
    if (root != NULL) {
        if(root->left == NULL && root->right == NULL && (*(unsigned char *)root->byte == '\\'|| *(unsigned char *)root->byte == '*' ))
        {
            preorder[*index] = '\\';
            (*index)++;
        }

        preorder[*index] = *(unsigned char *)root->byte;
        (*index)++;
        pre_order_tree(root->left, preorder, index);
        pre_order_tree(root->right, preorder, index);
    }
}

Node *construt_tree_preorder_data(unsigned char *tree, int *index, Node *arvore, int size) {

    if (*index < size)
    {
        if (tree[*index] == '*') { /* Caso seja um nó interno */
            unsigned char asterisco = '*';
            arvore = create_node(&asterisco, index);
            *index += 1;

            arvore->left = construt_tree_preorder_data(tree, index, arvore->left, size);
            arvore->right = construt_tree_preorder_data(tree, index, arvore->right, size);
        }
        else if (tree[*index] == '\\') { /* Caso seja encontrado um caracter de escape */
            *index += 1; /* considera o próximo caracter */

            unsigned char byte = tree[*index];
            arvore = create_node(&byte, index);

            *index += 1;
        }
        else /* Caso seja uma folha */
        {
            unsigned char byteAux = tree[*index];
            arvore = create_node(&byteAux, index);
            *index += 1;
        }
    }
    return arvore;
}

#endif 
