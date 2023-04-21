#include "./scheduler.h"
#include <time.h>


static int MICROSECONDS_IN_SECONDS = 1000000;
static int MAX_EXECUTING_CYCLES = 5;

int EXECUTING_CYCLES, TOTAL_PROCESSES, TOTAL_CPU_CYCLES;
double THROUGHPUT, TURNAROUND_TIME;


bool LOG_INFO = true;
int CPU_CYCLE_MICROSECONDS;

Process * executing_process = NULL;

Queue* finished_queue;
Queue* ready_queue;
Queue* bloqued_queue;
Queue* incoming_queue;


// INITIALIZATION / MEMORY COLLECTION

void init_scheduler_queues(){
    finished_queue = init_queue();
    ready_queue = init_queue();
    bloqued_queue = init_queue();
    incoming_queue = init_queue();
}

void init_scheduler_params(){
    EXECUTING_CYCLES = 0;
    TOTAL_PROCESSES = 0;
    TOTAL_CPU_CYCLES = 0;
    THROUGHPUT = 0;
    TURNAROUND_TIME = 0;
}

void add_process_to_scheduler(Process* process){
    TOTAL_PROCESSES += 1;
    if(process->CPU_start_cycle == 0){
        scheduling_enqueue(ready_queue, process);
        process->status = STATUS_READY;
    }
    else{
        enqueue(incoming_queue, process);
        process->status = STATUS_INCOMING;
    }  
}

void free_scheduler_memory(){
    free(finished_queue);
    free(ready_queue);
    free(bloqued_queue);
    free(incoming_queue);
}


// SCHEDULER INFO

double CYCLE_SECONDS_CORRECTION(){
    return ((double) CPU_CYCLE_MICROSECONDS)/MICROSECONDS_IN_SECONDS;
}

double CPU_TIME(){
    return TOTAL_CPU_CYCLES * CYCLE_SECONDS_CORRECTION();
}

void print_scheduler_info(){
    if(!LOG_INFO){
        return;
    }
    printf("\n--------------------\n");
    printf("TOTAL CPU CYCLES: %d\nTOTAL CPU TIME: %.3f [s]\n", TOTAL_CPU_CYCLES, CPU_TIME());
    printf("PROCESSES INFO\n");
    printf("[-] %s: \n", STATUS_FINISHED);
    print_queue(finished_queue);
    printf("[+] %s: \n", STATUS_EXECUTING);
    if(executing_process != NULL)
        print_process(executing_process);
    printf("[*] %s: \n", STATUS_READY);
    print_queue(ready_queue);
    printf("[!] %s: \n", STATUS_BLOQUED);
    print_queue(bloqued_queue);
    printf("[?] %s: \n", STATUS_INCOMING);
    print_queue(incoming_queue);
    printf("--------------------\n");
}

void print_scheduler_metrics(){
    printf("\n--------------------\n");
    printf("TOTAL_PROCESSES: %d\nTOTAL_CPU_CYCLES: %d\nTOTAL_CPU_TIME: %.3f [s]\nTHROUGHPUT: %.0f [P/h]\nTURNAROUND_TIME: %.3f [s]", 
        TOTAL_PROCESSES, TOTAL_CPU_CYCLES, CPU_TIME(), THROUGHPUT, TURNAROUND_TIME);
    printf("\n--------------------\n\n");
}

void inspect_queue_memdir(Queue* queue){
    printf("MEMDIR QUEUE: [%d, %d + %d]\n", queue, queue, sizeof(Queue));
    printf("MEMDIR HEAD: %d\n", &(queue->head));
    printf("MEMDIR TAIL: %d\n", &(queue->tail));
    printf("MEMDIR SIZE: %d\n", &(queue->size));
    printf("MEMDIR ITEMS[0]: %d\n", &(queue->items));
    printf("MEMDIR ITEMS[50]: %d\n", &(queue->items[50]));
    printf("MEMDIR ITEMS[100]: %d\n\n", &(queue->items[100]));
}

// SIMULATION STATUS

bool IO_interrupt(Process * process){
    return rand_probability() < process->IO_ratio;
}
bool IO_return(Process * process){
    return rand_probability() > process->IO_ratio;
}
bool no_executing_process(){
    return executing_process==NULL;
}
bool executing_process_finished(){
    return executing_process->CPU_total_cycles == executing_process->CPU_cycles;
}
bool max_time_reached(){
    return EXECUTING_CYCLES == MAX_EXECUTING_CYCLES;   
}
bool executing_process_interrupted(){
    return executing_process->status == STATUS_BLOQUED;
}
bool context_switching(){
    return no_executing_process() || executing_process_finished() || max_time_reached() || executing_process_interrupted();
}
bool all_processes_done(){
    return queue_empty(ready_queue) && queue_empty(bloqued_queue) && queue_empty(incoming_queue) && executing_process==NULL;
}

// SCHEDULER SIMULATION

void check_bloqued_processes(){
    Process * process = dequeue(bloqued_queue);
    if(process == NULL)
        return;
    if(IO_return(process)){
        scheduling_enqueue(ready_queue, process);
        process->status = STATUS_READY;
    }
    else{
        push(bloqued_queue, process);
        process->status = STATUS_BLOQUED;
    }   
}

void check_incoming_processes(){
    Queue* temp_queue = init_queue();
    while(!queue_empty(incoming_queue)){
        Process * process = dequeue(incoming_queue);
        if(process->CPU_start_cycle == TOTAL_CPU_CYCLES){
            scheduling_enqueue(ready_queue, process);
            process->status = STATUS_READY;
        }
        else{
            enqueue(temp_queue, process);
        }
    }
    while(!queue_empty(temp_queue)){
        enqueue(incoming_queue, dequeue(temp_queue));
    }  
}

void increment_time(){
    usleep(CPU_CYCLE_MICROSECONDS);
    TOTAL_CPU_CYCLES += 1;
    EXECUTING_CYCLES += 1;
    check_bloqued_processes();
    if(executing_process != NULL){
        executing_process->CPU_cycles += 1;
        if(!executing_process_finished()){
            if(IO_interrupt(executing_process)){
                executing_process->status = STATUS_BLOQUED;
            }
        }            
    }
    check_incoming_processes();
}

void do_context_switch(){
    if(executing_process != NULL){
        if(executing_process_finished()){
            enqueue(finished_queue, executing_process);
            executing_process->status = STATUS_FINISHED;
            executing_process->CPU_end_cycle = TOTAL_CPU_CYCLES;
            executing_process = NULL;
        }
        else if(max_time_reached()){
            scheduling_enqueue(ready_queue, executing_process);
            executing_process->status = STATUS_READY;
        }
        else if(executing_process_interrupted()){
            enqueue(bloqued_queue, executing_process);
            executing_process->status = STATUS_BLOQUED;
        }
    }
    EXECUTING_CYCLES = 0;
    executing_process = scheduling_dequeue(ready_queue);
    if(executing_process != NULL)
        executing_process->status = STATUS_EXECUTING;
}

void calculate_metrics(){
    THROUGHPUT = (TOTAL_PROCESSES/ CPU_TIME()) * 3600;
    double avg_elapsed_CPU_cycles = 0;
    while(!queue_empty(finished_queue)){
        Process* process = dequeue(finished_queue);
        avg_elapsed_CPU_cycles += process->CPU_end_cycle - process->CPU_start_cycle;
        free(process);
    }
    avg_elapsed_CPU_cycles = (double) avg_elapsed_CPU_cycles/TOTAL_PROCESSES;
    TURNAROUND_TIME = avg_elapsed_CPU_cycles * CYCLE_SECONDS_CORRECTION();
}

void run_simulation(){
    do_context_switch();
    print_scheduler_info();
    while(1){
        increment_time();
        if(context_switching()){
            do_context_switch();
            if(all_processes_done()){
                break;
            }
        }
        print_scheduler_info();
    }
    calculate_metrics();
    print_scheduler_metrics();
}


void interactive_simulation(){
    LOG_INFO = true;
    CPU_CYCLE_MICROSECONDS = MICROSECONDS_IN_SECONDS/5;
    run_simulation();
}

void benchmark_simulation(){
    LOG_INFO = false;
    CPU_CYCLE_MICROSECONDS = 1000;
    run_simulation();
}

