
#include "./queue.h"

Queue* init_queue(){
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    return queue;
}

bool queue_empty(Queue* queue){
    return queue->size == 0;
}

void enqueue(Queue* queue, Process* process){
    queue->items[queue->tail] = process;
    queue->tail = (queue->tail + 1) % NUM_PROCESSES;
    queue->size += 1;
}

Process* dequeue(Queue* queue){
    if(queue_empty(queue))
        return NULL;
    Process* process =  queue->items[queue->head];
    queue->head = (queue->head + 1) % NUM_PROCESSES;
    queue->size -= 1;
    return process;
}

// Enqueue at the head
void push(Queue* queue, Process* process){
    queue->head = (queue->head - 1 + NUM_PROCESSES) % NUM_PROCESSES;
    queue->items[queue->head] = process;
    queue->size += 1;
}

void print_queue(Queue* queue){
    if(queue_empty(queue))
        return;



    if(queue->head < queue->tail){
        for(int i=queue->head; i<queue->tail; i++){
            print_process(queue->items[i]);
        }
    }else{
        for(int i=queue->head; i<NUM_PROCESSES; i++){
            print_process(queue->items[i]);
        }
        for(int i=0; i<queue->tail; i++){
            print_process(queue->items[i]);
        }
    }
}

