#ifndef ADT_H
#define ADT_H

#include <stdio.h>
#include <stdlib.h>
#define ASCII_LENGTH 256

typedef struct _huff
{
    unsigned char byte;
    int cont;
    struct _huff *next;
    struct _huff *left;
    struct _huff *right;
} hufftree;

typedef struct huff_list
{
    int size;
    hufftree *head;
} Hlist;

/*
    # OBJETIVO: Verificar se a lista de prioridade está vazia
    # PARAMETRO: É passado um ponteiro para a lista de prioridade
    # RETORNO: É retornado 1 se a lista estiver vazia e 0 caso contrário
*/

int is_empty(Hlist *list);

/*
    # OBJETIVO: Adicionar um novo nó na lista de prioridade
    # PARAMETRO: É passado um ponteiro para a lista de prioridade, um ponteiro para o byte, um inteiro com a 
        frequência do byte, um ponteiro para a subárvore esquerda e um ponteiro para a subárvore direita
    # RETORNO: Não é retornado nada, mas é adicionado um novo node na lista de prioridade
*/

void enqueue_huff_list(Hlist *list, void *byte, int count, hufftree *left, hufftree *right);

/*
    # OBJETIVO: Criar uma lista de prioridade
    # PARAMETRO: É passado um array de inteiros com as frequências dos bytes
    # RETORNO: É retornado um ponteiro para a lista de prioridade
*/

Hlist *create_priority_queue(int *frequencies);








int is_empty(Hlist *list)
{
    return list->size == 0 || list->head == NULL;
}


void enqueue_huff_list(Hlist *list, void *byte, int count, hufftree *left, hufftree *right)
{
    hufftree *new_huff = (hufftree *)malloc(sizeof(hufftree));
    
    new_huff->byte = *(unsigned char *)byte;
    new_huff->cont = count;
    new_huff->left = left;
    new_huff->right = right;
    new_huff->next = NULL;

    if (is_empty(list))
    {
        list->head = new_huff;
    }
    else
    {
        hufftree *current = list->head;
        hufftree *previous = NULL;

        while (current != NULL && current->cont < new_huff->cont)
        {
            previous = current;
            current = current->next;
        }

        if (previous == NULL)
        {
            new_huff->next = list->head;
            list->head = new_huff;
        }
        else
        {
            previous->next = new_huff;
            new_huff->next = current;
        }
    }

    list->size++;

    return;
}

Hlist *create_priority_queue(int *frequencies)
{
    Hlist *list = (Hlist *)malloc(sizeof(Hlist));

    list->size = 0;
    list->head = NULL;

    for (int i = 0; i < ASCII_LENGTH; i++)
    {
        if (frequencies[i] != 0)
        {
            enqueue_huff_list(list, &i, frequencies[i], NULL, NULL);
        }
    }
    
    return list;
}

#endif 
