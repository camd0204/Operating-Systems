
#ifndef SCHEDULING_QUEUE
#define SCHEDULING_QUEUE

#include "./process.h"
#include "./queue.h"

void scheduling_enqueue(Queue* queue, Process* process);
Process* scheduling_dequeue(Queue* queue);

#endif
