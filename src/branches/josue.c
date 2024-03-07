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

    if(is_empty_queue(queue) || (new_node->priority < queue->head->priority) ){
        new_node->next = queue->head;
        queue->head = new_node;
        queue->size++;
        return;
    } 

    Node * current = queue->head;

    while (current->next != NULL &&  new_node->priority > current->next->priority)
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
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

    return queue->head;
}

void print_huff_tree(Node * huff_tree, int heigth){
    if(huff_tree->left == NULL && huff_tree->right == NULL){
        printf("leaf: %c - height: %d\n", huff_tree->byte ,heigth);
        return;
    }

    print_huff_tree(huff_tree->left, heigth + 1);
    print_huff_tree(huff_tree->right, heigth + 1);
}


int main(){
    Huff_Queue * queue = create_queue();

    
    enqueue_priority(queue, create_node('a', 5));
    enqueue_priority(queue, create_node('b', 1));
    enqueue_priority(queue, create_node('c', 3));
    enqueue_priority(queue, create_node('e', 6));
    enqueue_priority(queue, create_node('r', 9));

    struct node * current = queue->head;
    while (current != NULL)
    {
        printf("c:%c - f:%d - size: %d\n", current->byte, current->priority, queue->size);
        current = current->next;
    }


    Node * huffman_tree = create_huffman_tree(queue);
    print_huff_tree(huffman_tree, 0);
    
    return 0;

}