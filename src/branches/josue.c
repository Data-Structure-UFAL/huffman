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

void enqueue_priority(Huff_Queue * queue, int freq, unsigned char byte){
    Node * new_node = create_node(byte, freq);

    if(is_empty_queue(queue) || (freq < queue->head->priority) ){
        new_node->next = queue->head;
        queue->head = new_node;
        queue->size++;
        return;
    } 

    Node * current = queue->head;

    while (current->next != NULL &&  freq > current->next->priority)
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


Huff_Tree * create_huffman_tree(Huff_Queue * queue){
    Node *left, *right, *new_node;

    while (queue->size > 1)
    {
        left = dequeue(queue);
        right = dequeue(queue);
        new_node->left = left;
        new_node->right = right;
        enqueue_priority(queue, '*', left->priority + right->priority);
    }
}


int main(){
    Huff_Queue * queue = create_queue();

    enqueue_priority(queue, 30, 'd');
    Node * dequeued = dequeue(queue);
    printf("first: %c - size: %d\n", dequeued->byte, queue->size);
    enqueue_priority(queue, 20, 'a');
    enqueue_priority(queue, 10, 'z');
    enqueue_priority(queue, 12, 'j');
    dequeued = dequeue(queue);
    printf("first: %c - size: %d\n", dequeued->byte, queue->size);
    enqueue_priority(queue, 1, 'h');
    enqueue_priority(queue, 100, 'x');

    struct node * current = queue->head;
    while (current != NULL)
    {
        printf("c:%c - f:%d - size: %d\n", current->byte, current->priority, queue->size);
        current = current->next;
    }

    dequeued = dequeue(queue);
    printf("first: %c - size: %d", dequeued->byte, queue->size);
    
    return 0;

}