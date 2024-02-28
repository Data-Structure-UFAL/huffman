// Esboço para a fila de prioridade

/*
    Fiz o código pensando nesse tipo de structs

    typedef struct _huff
    {
        unsigned char byte;
        int cont;
        struct _huff *next;
        struct _huff *left;
        struct _huff *right;
    } hufftree;

    typedef struct temp_list
    {
        int size;
        struct hufftree *head;
    } temp_list;

*/

/*
    Recebe um array com as frquencias de bytes e uma lista encadeada os nodes são do tipo hufftree e retorna a fila de prioridade
    Assume que a lista encadeada já foi inicializada
*/

temp_list *create_priority_queue(temp_list *list, int **frequencies)
{
    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] != 0)
        {
            hufftree *new_huff = (hufftree *)malloc(sizeof(hufftree));
            
            new_huff->byte = i;
            new_huff->frequency = *frequencies[i];
            new_huff->next = NULL;
            new_huff->left = NULL;
            new_huff->right = NULL;

            if (list->head == NULL)
            {
                list->head = new_huff;
            }
            else
            {
                hufftree *current = list->head;
                hufftree *previous = NULL;

                while (current != NULL && current->frequency < new_huff->frequency)
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
        }
    }

    return list;
}