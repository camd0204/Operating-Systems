
#include "./scheduling_algorithm.h"

void scheduling_enqueue(Queue* queue, Process* process){
    if(queue_empty(queue)){
        enqueue(queue, process);
        return;
    }
    Process * current_process = NULL;
    for(int i=queue->head; i%NUM_PROCESSES<queue->tail; i++){
        current_process = queue->items[i%NUM_PROCESSES];
        if(process->CPU_total_cycles < current_process->CPU_total_cycles){
            queue->items[i%NUM_PROCESSES] = process;
            process = current_process;
        }
    }
    enqueue(queue, process);
}

Process* scheduling_dequeue(Queue* queue){
    dequeue(queue);
}