#ifndef ADT_H
#define ADT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_LENGTH 256

typedef struct node {
	int priority;
    unsigned char byte;
	struct node *next;
    struct node *left;
    struct node *right;
} Node;

typedef struct {
    Node * head;
    int size;
} Huff_Queue;

typedef struct {
    Node * root;
} Huff_Tree;

/*
    - OBJETIVO: Criar um nó
    - PARAMETRO: É passado dois parâmetros, um informando o byte e outro a frequência daquele byte
    - RETORNO: É retornado um nó com as informações passadas
*/
Node * create_node(unsigned char byte, int frequency);

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
- Objetivo: Alocar e instanciar uhm No
- Parametro: Um Byte e a Frequencia do byte
- Retorno: Um No alocado e instanciado  
*/
Node * create_node(unsigned char byte, int frequency){
    Node *new_node = malloc(sizeof(Node));
	new_node->priority = frequency;
    new_node->byte = byte;
    new_node->left = NULL; 
    new_node->right = NULL; 
    return new_node;
}

/* 
- Objetivo: Instancia uma lista 
- Parametro: Sem parametros
- Retorno: Um struct contendo um ponteiro para o inicio da lista e o tamanho atual 
*/
Huff_Queue * create_queue(){
    Huff_Queue * new_queue = malloc(sizeof(Huff_Queue));
    new_queue->head = NULL;
    new_queue->size = 0;
    return new_queue;
}

/* 
- Objetivo: Verificar se a lista esta vazia
- Parametro: Uma Lista
- Retorno: Um inteiro representando true ou false
*/
int is_empty_queue(Huff_Queue * queue){
    return queue->head == NULL;
}

/* 
- Objetivo: Adicionar um no na lista de forma crescente
- Parametro: Lista,e o No a ser adicionado
- Retorno: Sem retorno, a lista eh alterada por referencia
*/
void enqueue_priority(Huff_Queue * queue, Node * new_node){
   /*  Node * new_node = create_node(byte, freq); */

    if(is_empty_queue(queue) || (new_node->priority <= queue->head->priority)){
        new_node->next = queue->head;
        queue->head = new_node;
        queue->size++;
        return;
    } 

    Node * current = queue->head;

    while (current->next != NULL && (new_node->priority > current->next->priority)){
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node; /* verificar isso aqui dps */
    queue->size++;
}

/* CREATE TREE HUFFMAN */
/* 
- Objetivo: Remover o primeiro no da lista
- Parametro: Uma lista
- Retorno: O no removido 
*/
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

/* 
- Objetivo: Construir a arvore de huffman
- Parametro: Um no apontando para o inicio de uma lista de prioridades
- Retorno: Um no apontando para a raiz da arvore
*/
Node * create_huffman_tree(Huff_Queue * queue){
    Node *left, *right, *new_node;

    while (queue->size > 1)
    {
        left = dequeue(queue);
        right = dequeue(queue);
        new_node = create_node('*', left->priority + right->priority); // Allocate memory for the new node
        new_node->left = left;
        new_node->right = right;
        enqueue_priority(queue, new_node);
        
    }

    return dequeue(queue);
}

/* 
- Objetivo: Calcular a altura da arvore
- Parametro: Um no apontando para a raiz da arvore
- Retorno: Um inteiro representando a altura
*/
int tree_height(Node * root){
    int left, right;

    if(root == NULL) return - 1;

    left = tree_height(root->left);
    right = tree_height(root->right);

    return (left > right) ? left + 1: right + 1; 
}

/* 
- Objetivo: Fazer alocação de memória do dicionário
- Parametro: Um inteiro representndo o numero de colunas
- Retorno: Um ponteiro que aponta para um array de strings
*/
char ** create_empty_dictionary(int column){ /* Remember to use CONST LENGTH_ASCII and not 256*/
    char **dictionary;
    dictionary = malloc(sizeof(char*) * 256); 

    for (int i = 0; i < 256; i++)
        dictionary[i] =  calloc(column, sizeof(char));

    return dictionary;
}

/* 
- Objetivo: Criar um dicionário que referencia o caminho das folhas de um byte 
- Parametro: Dicionario Alocado, Raiz, Caminho Vazio, Numero de Colunas
- Retorno: Sem retorno... altera o dicionário por referencia
*/
void create_dictionary(char **dictionary, Node *root, char *path, int column) {
    char left[column], right[column];

    if (root->left == NULL && root->right == NULL) {
        strcpy(dictionary[root->byte], path);
    } else {
        strcpy(left, path);
        strcpy(right, path);

        strcat(left, "0");
        strcat(right, "1");

        create_dictionary(dictionary, root->left, left, column);
        create_dictionary(dictionary, root->right, right, column);
    }
}


void print_dictionary(char ** dictionary){
    for (int i = 0; i < 256; i++)
    {
        if(strlen(dictionary[i]) > 0)
            printf("\t%3c: %s\n", i, dictionary[i]);
    }
    
}

void print_huff_tree(Node * huff_tree, int heigth){
    if(huff_tree->left == NULL && huff_tree->right == NULL){
        printf("leaf: %c - height: %d\n", huff_tree->byte ,heigth);
        return;
    }

    print_huff_tree(huff_tree->left, heigth + 1);
    print_huff_tree(huff_tree->right, heigth + 1);
}


/* CODIFICAÇÃO DO TEXTO */

/* 
- Objetivo: Calcular o numero de bits com referencia ao dicionario
- Parametro: Dicionario, Texto
- Retorno: Um inteiro representando o numero de bits
*/
int size_text_coding(char ** dictionary, object_data * data){
    int length = 0, i = 0;

    for (int i = 0; i < data->size; i++)
    {
        length += strlen(dictionary[data->byte[i]]);
    }
    
    return length;
}
/* 
- Objetivo: Codificar um texto em bits (formato de texto) com base no dicionario
- Parametro: Dicionario, Texto
- Retorno: Uma string de um texto codificado
*/
char * coding_text(char ** dictionary, object_data * data){
    int size =  size_text_coding(dictionary, data) + 1;
    char * code = calloc(size, sizeof(char));

   for (int i = 0; i < data->size; i++)
   {
     strcat(code, dictionary[data->byte[i]]);
   }
   
    return code;
}

/* DECODING JUST TEXT TO LERANING */

/* 
- Objetivo: Decodificar uma sequencia de bits (char) no texto original
- Parametro: Texto codificado, Raiz da Arvore de  Huffman
- Retorno: Uma string decodificada 
*/
unsigned char * decoding_text(char text[], Node * root){
    int i = 0;
    Node * aux = root;
    char temp[2];
    unsigned char * decoding = calloc(strlen(text) , sizeof(unsigned char));


    while (text[i] != '\0')
    {
       
        if(text[i] == '0')
            aux = aux->left;
        else     
            aux = aux->right;

        if (aux->left == NULL && aux->right == NULL)
        {
            temp[0] = aux->byte;
            temp[1] = '\0';

            strcat(decoding, temp);
            aux = root;
        }

        i++;
    }

    return decoding;
}


int trash_size(char ** dictionary, object_data * data){
    return 8 - (size_text_coding(dictionary, data) % 8);
}

int size_tree(Node * node){
    if(node == NULL){
        return 0;
    }
 
    if(node->left == NULL && node->right == NULL && (node->byte == '*' || node->byte == '\\')) {
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

void decoding(Node * root, int qts_bytes_completos){
    FILE * compress_file = fopen("compress.huff", "rb");

    if(!compress_file){
        printf("Problema ao abrir arquivo em compress_file\n");
        return;
    }

    FILE  * decompress_file = fopen("decompress.txt", "wb");
    if(!decompress_file){
        printf("Problema ao abrir arquivo em decompress_file\n");
        return;
    }

    unsigned char byte;
    Node * current = root;



    while (fread(&byte, sizeof(unsigned char), 1, compress_file))
    {
        
        for (int i = 7; i >= 0; i--)        
        {
            
            current = (is_on_bit(byte, i)) ? current->right : current->left;

            if(qts_bytes_completos < 0) break;

            if(current->left == NULL && current->right == NULL){
                /* printf("qtdbits: %d decompress... %c\n", qts_bytes_completos, current->byte); */
                fwrite(&current->byte, sizeof(unsigned char), 1, decompress_file);
                current = root;
            }
            qts_bytes_completos--;
        }
    }

    fclose(compress_file);
    fclose(decompress_file);
}


//FUNCAO DE TESTE PARA FINS DE TESTE

int teste(int i)
{
    if(i == 1) return 0;

    return 1;
}

void pre_order_tree(Node * root, char * preorder, int *index)
{
    if (root != NULL) {
        if(root->left == NULL && root->right == NULL && (root->byte == '\\'|| root->byte == '*' ))
        {
            preorder[*index] = '\\';
            (*index)++;
        }

        preorder[*index] = root->byte;
        (*index)++;
        pre_order_tree(root->left, preorder, index);
        pre_order_tree(root->right, preorder, index);
    }
}

Node *read_pre_order(unsigned char *tree, int *index, Node *arvore, int size) {

    if (*index < size)
    {
        if (tree[*index] == '*') {
            // Create a new node with the special character '*'
            arvore = create_node('*', 0);
            *index += 1;

            // Recursively read left and right subtrees
            arvore->left = read_pre_order(tree, index, arvore->left, size);
            arvore->right = read_pre_order(tree, index, arvore->right, size);
        }
        else if (tree[*index] == '\\') {
            // Move to the next character
            *index += 1;
            
            // Create a new node with the character following '\'
            arvore = create_node(tree[*index], 0);

            // Move to the next character
            *index += 1;
        }
        else
        {
            // Create a new node with the current character
            arvore = create_node(tree[*index], 0);

            // Move to the next character
            *index += 1;
        }

    }
    return arvore;
}

void print_pre_order(Node *arvore) {
    if (arvore != NULL) {
        printf("%c ", arvore->byte);
        print_pre_order(arvore->left);
        print_pre_order(arvore->right);
    }
}

#endif 
