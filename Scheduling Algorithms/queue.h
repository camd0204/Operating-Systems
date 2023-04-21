#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#include <stdbool.h>
#include "./process.h"

typedef struct Queue{
    Process* items[NUM_PROCESSES];
    int head;
    int tail;
    int size;
} Queue;

Queue* init_queue();
bool queue_empty(Queue* queue);
void enqueue(Queue* queue, Process* process);
Process* dequeue(Queue* queue);
void push(Queue* queue, Process* process);
void print_queue(Queue* queue);

#endif