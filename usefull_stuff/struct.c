typedef struct _huff
{
    unsigned char byte;
    int cont;
    struct _huff *next;
    struct _huff *left;
    struct _huff *right;
} hufftree;