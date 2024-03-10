#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    void *size;
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

// testar // ==========================================================================
void print_in_order(Node *root);

void print_queue(Huff_Queue *queue);

// =====================================================================================

int main()
{
    Huff_Queue *queue = create_queue();

    int freq[ASCII_LENGTH] = {0};

    char *text = "@#$%&((()))!@#@@";

    int tam = strlen(text);

    for (int i = 0; i < tam; i++)
    {
        freq[(uint8_t)text[i]]++;
    }

    for (int i = 0; i < ASCII_LENGTH; i++)
    {
        if (freq[i] > 0)
        {
            Node *new_node = create_node(&i, &freq[i]);

            enqueue_priority(queue, new_node);
        }
    }

    print_queue(queue);

    Node *root = create_huffman_tree(queue);

    print_in_order(root);

    return 0;
}

Node *create_node(void *byte, void* frequency)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    int *priority = (int *)malloc(sizeof(int));
    *priority = *(int *)frequency;

    uint8_t *new_byte = (uint8_t *)malloc(sizeof(uint8_t));
    *new_byte = *(uint8_t *)byte;

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

    int *size = (int *)malloc(sizeof(int));
    *size = 0;
    new_queue->size = size;

    return new_queue;
}

int is_empty_queue(Huff_Queue *queue)
{
    return queue->head == NULL;
}

void enqueue_priority(Huff_Queue *queue, Node *new_node)
{
    /*  Node * new_node = create_node(byte, freq); */

    if (is_empty_queue(queue) || (*(int *)new_node->priority < *(int *)queue->head->priority) ||
        (*(int *)new_node->priority == *(int *)queue->head->priority && *(uint8_t *)new_node->byte < *(uint8_t *)queue->head->byte))
    {

        new_node->next = queue->head;
        queue->head = new_node;

        *(int *)(queue->size) += 1;

        return;
    }

    Node *current = queue->head;

    while (current->next != NULL &&
           (*(int *)new_node->priority > *(int *)current->next->priority ||
            (*(int *)new_node->priority == *(int *)current->next->priority && *(uint8_t *)new_node->byte > *(uint8_t *)current->next->byte)))
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node; /* verificar isso aqui dps */

    *(int *)(queue->size) += 1;
}

/* CREATE TREE HUFFMAN */
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

    *(int *)queue->size -= 1;

    return dequeued;
}

Node *create_huffman_tree(Huff_Queue *queue)
{
    Node *left, *right, *new_node;

    while (*(int *)queue->size > 1)
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


//==================================================================================================================

void print_queue(Huff_Queue *queue)
{
    Node *current = queue->head;

    while (current != NULL)
    {
        printf("%c %d\n", *(unsigned char *)current->byte, *(int *)current->priority);
        current = current->next;
    }
}

void print_in_order(Node *root)
{
    if (root != NULL)
    {
        print_in_order(root->left);
        printf("%c %d\n", *(unsigned char *)root->byte, *(int *)root->priority);
        print_in_order(root->right);
    }
}