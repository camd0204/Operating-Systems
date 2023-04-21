#ifndef SCHEDULER
#define SCHEDULER

#include <unistd.h>
#include <stdbool.h>

#include "./util.h"
#include "./process.h"
#include "./queue.h"
#include "./scheduling_algorithm.h"

void init_scheduler_queues();
void init_scheduler_params();
void print_scheduler_info();
void print_scheduler_metrics();

void add_process_to_scheduler(Process* process);
void interactive_simulation();
void benchmark_simulation();
void free_scheduler_memory();

#endif
