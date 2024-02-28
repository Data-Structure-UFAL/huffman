#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

struct node {
	int priority;
    unsigned char byte;
	struct node *next;
    struct node *left;
    struct node *right;
};

struct queue {
	struct node *head, *tail;
};

struct queue * create_queue(){
    struct queue * new_queue = malloc(sizeof(struct queue));
    new_queue->head = new_queue->tail = NULL;
    return new_queue;
}

int is_empty_queue(struct queue * queue){
    return queue->head == NULL;
}

void priority_queue(struct queue * queue, int item){
	struct node *new_node = malloc(sizeof(struct node));
	new_node->priority = item;

    if(is_empty_queue(queue)|| (item > queue->head->priority) ){
        new_node->next = queue->head;
        queue->head = new_node;
        return;
    } 

    struct node * current = queue->head;

    while (current->next != NULL && current->next->priority > item)
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

void enqueue(struct queue * queue, int item, unsigned char byte){

    struct node *new_node = malloc(sizeof(struct node));
	new_node->priority = item;
    new_node->byte = byte;

    if(is_empty_queue(queue)){
        new_node->next = queue->head;
        queue->head = new_node;
        queue->tail = new_node;
        return;
    }

    queue->tail->next = new_node;
    queue->tail = new_node;
    new_node->next = queue->tail;

    queue->tail = new_node;
    queue->tail->next = NULL;
}


int main(){
   struct queue * queue = create_queue();

    enqueue(queue, 30, 'd');
    enqueue(queue, 20, 'a');
    enqueue(queue, 10, 'z');
    enqueue(queue, 12, 'j');
    enqueue(queue, 1, 'h');
    enqueue(queue, 100, 'x');

    struct node * current = queue->head;
    while (current != NULL)
    {
        printf("c:%c - f:%d\n", current->byte, current->priority);
        current = current->next;
    }
    
    return 0;

}