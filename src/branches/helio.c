#include <stdio.h>
#include <stdlib.h>

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

    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] != 0)
        {
            enqueue_huff_list(list, &i, frequencies[i], NULL, NULL);
        }
    }
    
    return list;
}

void print_priority_queue(Hlist *list)
{
    hufftree *current = list->head;
    
    while (current != NULL)
    {
        printf("%c: %d\n", current->byte, current->cont);
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

    Hlist *priority_queue = create_priority_queue(frequencies);

    print_priority_queue(priority_queue);

    return 0;
}
