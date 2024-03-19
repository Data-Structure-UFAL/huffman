#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adtHelio.h"
#define TAM 11

Node *read_pre_order(unsigned char *tree, int *index, Node *arvore, int size) {

    if (*index < size)
    {
        if (tree[*index] == '*') {
            arvore = create_node(tree + *index, index);
        
            *index += 1;

            arvore->left = read_pre_order(tree, index, arvore->left, size);
            arvore->right = read_pre_order(tree, index, arvore->right, size);
        }
        else if (tree[*index] == '\\') {
            *index += 1;
            
            arvore = create_node(tree + *index, index);

            *index += 1;
        }
        else
        {
            arvore = create_node(tree + *index, index);

            *index += 1;
        }

    }

    return arvore;
}


void print_pre_order(Node *arvore) {
    if (arvore != NULL) {
        printf("%c ", *(unsigned char *)arvore->byte);
        print_pre_order(arvore->left);
        print_pre_order(arvore->right);
    }
}

int main() {
    unsigned char texto[TAM] = {'*', '*', '*', 'a', 'b', '\\', '*', '*', 'd', 'e', '\0'};

    Huff_Tree *arvore = (Huff_Tree *)malloc(sizeof(Huff_Tree));
    arvore->root = NULL;

    int index = 0;

    printf("%d\n", strlen((char *)texto));

    arvore->root = read_pre_order(texto, &index, arvore->root, strlen((char *)texto));

    print_pre_order(arvore->root);

    return 0;
}