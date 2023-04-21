
#ifndef PROCESS
#define PROCESS

#include <stdio.h>

#include "./util.h"

#define NUM_PROCESSES 100

static char * STATUS_FINISHED = "FINISHED";
static char * STATUS_EXECUTING = "EXECUTING";
static char * STATUS_READY = "READY";
static char * STATUS_BLOQUED = "BLOQUED";
static char * STATUS_INCOMING = "INCOMING";

typedef struct Process{
    int ID;
    int priority;
    char* status;
    int CPU_start_cycle;
    int CPU_end_cycle;
    int CPU_total_cycles;
    int CPU_cycles;
    double IO_ratio;
} Process;

Process* init_input_process();
Process* init_random_IO_process();
Process* init_random_CPU_process();

void print_process(Process* process);

#endif
