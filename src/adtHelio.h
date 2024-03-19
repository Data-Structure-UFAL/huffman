#ifndef ADTHELIO_H
#define ADTHELIO_H

#include <stdio.h>
#include <stdlib.h>
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
    # OBJETIVO: Criar um nó
    # PARAMETRO: É passado dois parâmetro, um informando o byte e outro a frequência daquele byte
    # RETORNO: É retornado um nó com as informações passadas
*/
Node *create_node(void *byte, void *frequency);

/*
    # OBJETIVO: Criar uma lista
    # PARAMETRO: Não tem parâmetro
    # RETORNO: É retornado o head da lista apontando para NULL
*/
Huff_Queue *create_queue();

/*
    # OBJETIVO: Verificar se a lista de prioridade está vazia
    # PARAMETRO: É passado um ponteiro para a lista de prioridade
    # RETORNO: É retornado 1 se a lista estiver vazia e 0 caso contrário
*/
int is_empty_queue(Huff_Queue *queue);

/*
    # OBJETIVO: Adicionar de forma ordenada um novo nó na lista de prioridade
    # PARAMETRO: É passado um ponteiro para a lista de prioridade, e  o nó que deve ser adicionado
    # RETORNO: Não é retornado nada, mas é adicionado um novo node na lista de prioridade
*/
void enqueue_priority(Huff_Queue *queue, Node *new_node);

/*
    # OBJETIVO: Remover o head de uma Lista
    # PARAMETRO: É passado a Lista como parâmetro
    # RETORNO: É retornado o nó removido
*/

Node *dequeue(Huff_Queue *queue);

/*
    # OBJETIVO: Criar uma árvore de huffman
    # PARAMETRO: É passado a Lista como parâmetro
    # RETORNO: É retornado um nó representando o a Raiz da arvore montada
*/
Node *create_huffman_tree(Huff_Queue *queue);



Node *create_node(void *byte, void* frequency) 
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    int *priority = (int *)malloc(sizeof(int));
    *priority = *(int *)frequency;

    unsigned char *new_byte = (unsigned char *)malloc(sizeof(unsigned char));
    *new_byte = *(unsigned char *)byte;

    new_node->priority = priority;
    new_node->byte = new_byte;
    
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

Huff_Queue *create_queue()
{
    Huff_Queue *new_queue = (Huff_Queue *)malloc(sizeof(Huff_Queue));

    new_queue->head = NULL;
    new_queue->size = 0;

    return new_queue;
}

int is_empty_queue(Huff_Queue *queue)
{
    return queue->head == NULL;
}

void enqueue_priority(Huff_Queue *queue, Node *new_node)
{
    if (is_empty_queue(queue) || (*(int *)new_node->priority < *(int *)queue->head->priority) ||
        (*(int *)new_node->priority == *(int *)queue->head->priority && *(unsigned char *)new_node->byte < *(unsigned char *)queue->head->byte))
    {

        new_node->next = queue->head;
        queue->head = new_node;
        queue->size++;

        return;
    }

    Node *current = queue->head;

    while (current->next != NULL &&
           (*(int *)new_node->priority > *(int *)current->next->priority ||
            (*(int *)new_node->priority == *(int *)current->next->priority && *(unsigned char *)new_node->byte > *(unsigned char *)current->next->byte)))
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;

    queue->size++;
}

Node *dequeue(Huff_Queue *queue)
{
    if (is_empty_queue(queue))
    {
        printf("Queue Underflow\n");
        abort();
    }

    Node *dequeued = queue->head;

    queue->head = queue->head->next;
    dequeued->next = NULL;

    queue->size--;

    return dequeued;
}

Node *create_huffman_tree(Huff_Queue *queue)
{
    Node *left, *right, *new_node;

    while (queue->size > 1)
    {
        left = dequeue(queue);
        right = dequeue(queue);

        unsigned char asterisco = '*';
        int sum_priority = *(int *)left->priority + *(int *)right->priority;

        new_node = create_node(&asterisco, &sum_priority);

        new_node->left = left;
        new_node->right = right;

        enqueue_priority(queue, new_node);
    }

    return dequeue(queue);
}

#endif