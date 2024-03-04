#include <stdio.h>
#include <stdlib.h>

typedef struct huff_node
{
    int priority;
    unsigned char byte;
    struct huff_node *next;
    struct huff_node *left;
    struct huff_node *right;
} Huff_Node;

typedef struct huff_list
{
    int size;
    Huff_Node *head;
} Huff_Queue;

int is_empty_queue(Huff_Queue *list)
{
    return list->head == NULL;
}

void enqueue_huff_list(Huff_Queue *list, void *byte, int frequency, Huff_Node *left, Huff_Node *right)
{
    Huff_Node *new_huff = (Huff_Node *)malloc(sizeof(Huff_Node));
    
    new_huff->byte = *(unsigned char *)byte;
    new_huff->priority = frequency;
    new_huff->left = left;
    new_huff->right = right;
    new_huff->next = NULL;

    if (is_empty_queue(list))
    {
        list->head = new_huff;
    }
    else
    {
        Huff_Node *current = list->head;
        Huff_Node *previous = NULL;

        while (current != NULL && current->priority < new_huff->priority)
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

Huff_Queue * create_queue()
{
    Huff_Queue * new_queue = malloc(sizeof(Huff_Queue));
    
    new_queue->head = NULL;
    new_queue->size = 0;
    
    return new_queue;
}

Huff_Queue *create_priority_queue(int frequencies[])
{
    Huff_Queue *list = create_queue();

    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] != 0)
        {
            enqueue_huff_list(list, &i, frequencies[i], NULL, NULL);
        }
    }
    
    return list;
}

void print_priority_queue(Huff_Queue *list)
{
    Huff_Node *current = list->head;
    int sum = 0;
    
    while (current != NULL)
    {
        printf("%c: %d\n", current->byte, current->priority);
        current = current->next;
    }

    return;
}

int main()
{
    int frequencies[256];

    for (int i = 0; i < 256; i++)
    {
        frequencies[i] = i;
    }

    Huff_Queue *priority_queue = create_priority_queue(frequencies);

    print_priority_queue(priority_queue);

    return 0;
}
