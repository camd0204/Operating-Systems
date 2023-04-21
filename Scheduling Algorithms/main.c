
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./util.h"
#include "./process.h"
#include "./scheduler.h"

void read_input_processes(){
    printf("\nNumber of processes: ");
    int num_processes;
    scanf("%d", &num_processes);
    for(int i=0; i<num_processes; i++){
        Process* process = init_input_process();
        add_process_to_scheduler(process);
    }
}

void generate_random_processes(int num_processes, double IO_proportion){
    Process* process = NULL;
    for(int i=0; i<num_processes; i++){
        if(rand_probability()<IO_proportion){
            process = init_random_IO_process();
        }else{
            process = init_random_CPU_process();
        }
        add_process_to_scheduler(process);
    }
}

int run_benchmark(double IO_proportion){
    int num_repetitions = 10;
    printf("\n\n--------------------> IO/CPU: %.2f/%.2f\n\n", IO_proportion, 1 - IO_proportion);
    for(int i=0; i<num_repetitions; i++){
        printf("* Repetition %d\n", i + 1);
        init_scheduler_params();
        generate_random_processes(NUM_PROCESSES, IO_proportion);
        benchmark_simulation();
    }
}

void test(){
    init_scheduler_queues();
    init_scheduler_params();
    for(int i=0; i<100; i++)
        add_process_to_scheduler(init_random_IO_process());
    interactive_simulation();
}

int main(int argc, char const *argv[]){
    srand(time(NULL));
    init_scheduler_queues();
    run_benchmark(0.1);
    run_benchmark(0.5);
    run_benchmark(0.9);
    // test();
    free_scheduler_memory();
    return 0;
}
