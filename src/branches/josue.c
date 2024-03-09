#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

/* CREATE THE PRIORITY QUEUE*/

Node * create_node(unsigned char byte, int frequency){
    Node *new_node = malloc(sizeof(Node));
	new_node->priority = frequency;
    new_node->byte = byte;
    return new_node;
}

Huff_Queue * create_queue(){
    Huff_Queue * new_queue = malloc(sizeof(Huff_Queue));
    new_queue->head = NULL;
    new_queue->size = 0;
    return new_queue;
}

int is_empty_queue(Huff_Queue * queue){
    return queue->head == NULL;
}

void enqueue_priority(Huff_Queue * queue, Node * new_node){
   /*  Node * new_node = create_node(byte, freq); */

    if(is_empty_queue(queue) || (new_node->priority < queue->head->priority) ||
        (new_node->priority == queue->head->priority && new_node->byte < queue->head->byte)){
        new_node->next = queue->head;
        queue->head = new_node;
        queue->size++;
        return;
    } 

    Node * current = queue->head;

    while (current->next != NULL &&
           (new_node->priority > current->next->priority ||
            (new_node->priority == current->next->priority && new_node->byte > current->next->byte))) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node; /* verificar isso aqui dps */
    queue->size++;
}

/* CREATE TREE HUFFMAN */
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

void print_huff_tree(Node * huff_tree, int heigth){
    if(huff_tree->left == NULL && huff_tree->right == NULL){
        printf("leaf: %c - height: %d\n", huff_tree->byte ,heigth);
        return;
    }

    print_huff_tree(huff_tree->left, heigth + 1);
    print_huff_tree(huff_tree->right, heigth + 1);
}

/* Create the dictionary */

int tree_height(Node * root){
    int left, right;

    if(root == NULL) return -1;

    left = tree_height(root->left);
    right = tree_height(root->right);

    return (left > right) ? left + 1: right + 1; 
}

char ** create_empty_dictionary(int column){ /* Remember to use CONST LENGTH_ASCII and not 256*/
    char **dictionary;
    dictionary = malloc(sizeof(char*) * 256); 

    for (int i = 0; i < 256; i++)
        dictionary[i] =  calloc(column, sizeof(char));

    return dictionary;
}

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


/* CODING JUST TEXT TO LEARNING */ 

int size_text_coding(char ** dictionary, char * text){
    int length = 0, i = 0;

    while (text[i] != '\n')
    {
        length += strlen(dictionary[text[i]]);
        i++;
    }
    return length + 1;
}

char * coding_text(char ** dictionary, unsigned char * text){
    int i = 0, size =  size_text_coding(dictionary, text);

    char * code = calloc(size, sizeof(char));

    while (text[i] != '\n')
    {
        strcat(code, dictionary[text[i]]);
        i++;
    }

    return code;
    
}

/* DECODING JUST TEXT TO LERANING */

char * decoding_text(unsigned char text[], Node * root){
    int i = 0;
    Node * aux = root;
    char temp[2];
    char * decoding = calloc(strlen(text) , sizeof(char));


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


/* CODING IN ARCHIVE */

void coding(char * text_coded){/* 0011100001 */
    FILE * file = fopen("compress.medino", "wb");

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

void decoding(Node * root){
    FILE * file = fopen("compress.medino", "rb");

    if(!file){
        printf("Problema ao abrir arquivo em Decoding()\n");
        return;
    }

    unsigned char byte; 
    Node * current = root;
    while (fread(&byte, sizeof(unsigned char), 1, file))
    {
        for (int i = 7; i > - 0; i--)        
        {
            current = (is_on_bit(byte, i)) ? current->right : current->left;

            if(current->left == NULL && current->right == NULL){
                printf("decoding:%c\n", current->byte);
                current = root;
            }
        }
    }

    fclose(file);
}

int main(){
    Huff_Queue * queue = create_queue();

    
    enqueue_priority(queue, create_node('a', 5));
    enqueue_priority(queue, create_node('b', 1));
    enqueue_priority(queue, create_node('c', 3));
    enqueue_priority(queue, create_node('e', 6));
    enqueue_priority(queue, create_node('r', 8));

    
    struct node * current = queue->head;
    while (current != NULL)
    {
        printf("c:%c - f:%d - size: %d\n", current->byte, current->priority, queue->size);
        current = current->next;
    }
   
    Node * huffman_tree = create_huffman_tree(queue);
    int h = tree_height(huffman_tree);
    printf("%d\n", h); 

    

    int column = tree_height(huffman_tree) + 1;
    char ** dictionary = create_empty_dictionary(column);
    create_dictionary(dictionary, huffman_tree, "", column);

    print_dictionary(dictionary);
    

    char * text_coded;
    char * inicial_string = "aaaaabccceeeeeerrrrrrrr";
    text_coded = coding_text(dictionary,  inicial_string);


    printf("\n\t%s\n", text_coded);



    char * text_decoding; 
    text_decoding = decoding_text(text_coded, huffman_tree);

    printf("\t\n %s\n", text_decoding);

    coding(text_coded);
    decoding(huffman_tree);
    
    return 0;

}