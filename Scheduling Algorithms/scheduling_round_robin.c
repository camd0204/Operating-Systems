#include "./scheduling_algorithm.h"

void scheduling_enqueue(Queue* queue, Process* process){
    enqueue(queue, process);
}

Process* scheduling_dequeue(Queue* queue){
    return dequeue(queue);
}