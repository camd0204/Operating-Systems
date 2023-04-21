
#include "./process.h"

int CURRENT_PID = 0;

Process* init_process(){
    Process* process = (Process*) malloc(sizeof(Process));
    process->ID = CURRENT_PID ++;
    if(process->CPU_start_cycle==0)
        process->status = STATUS_READY;
    else
        process->status = STATUS_INCOMING;
    process->CPU_cycles = 0;
    process->CPU_end_cycle = -1;
    return process;
}

Process* init_input_process(){
    Process* process = init_process();
    printf("Process [%d]\n", process->ID);
    printf("(Priority, CPU_Start_Cycle, CPU_Total_Cycles, IO_ratio): ");
    scanf("%d %d %d %.2f", &process->priority, &process->CPU_start_cycle, &process->CPU_total_cycles, &process->IO_ratio);
    return process;
}

// RANDOM PROCESSES

Process* init_random_process(){
    Process* process = init_process();
    process->priority = int_rand_range(0,139); 
    process->CPU_start_cycle = 0;
    process->CPU_total_cycles = int_rand_range(10, 100);
    return process;
}

Process* init_random_IO_process(){
    Process* process = init_random_process();
    process->IO_ratio = rand_range(0.5, 0.8);
    return process;
}

Process* init_random_CPU_process(){
    Process* process = init_random_process();
    process->IO_ratio = rand_range(0.05, 0.4);
    return process;
}


// PRINT

void print_process(Process* process){
    printf("[Process] ID:%d - Priority:%d - CPU_Start_Cycle:%d - CPU_End_Cycle:%d - CPU_Total_Cycles:%d - IO_ratio:%.2f - State:%s - CPU_Cycles:%d\n", 
            process->ID, process->priority, process->CPU_start_cycle, process->CPU_end_cycle, process->CPU_total_cycles, 
            process->IO_ratio, process->status, process->CPU_cycles);
}