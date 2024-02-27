typedef struct _huff
{
    unsigned char byte;
    int cont;
    struct _huff *next;
    struct _huff *left;
    struct _huff *right;
} hufftree;

#include <stdio.h>

//FUNCAO QUE PODE SER UTIL
unsigned long long int sizeArchive(FILE *file) {
    // Salva a posição atual do cursor no arquivo
    long long int currentPosition = ftell(file);

    // Move o cursor para o final do arquivo
    fseek(file, 0, SEEK_END);

    // Obtém a posição atual do cursor, que corresponde ao tamanho do arquivo
    unsigned long long int size = ftell(file);

    // Restaura a posição original do cursor
    fseek(file, currentPosition, SEEK_SET);

    return size;
}
