# Scheduling Algorithm Simulator

The simulator has two modes: interactive simulation and benchmark simulation

## Compilation
```
gcc -o ./out/<scheduling_algorithm>_scheduling_simulator main.c process.c queue.c scheduler.c <scheduling_algorithm> 
```
Replace <scheduling_algorithm> by the desired implementation.


## Interactive Execution

Run the executable
```
gcc -o ./out/<scheduling_algorithm>_scheduling_simulator
```
Input values for processes. Some examples of processes are the following:

Without IO:
```
5
2 0 9 0
4 0 7 0
4 0 5 0
1 2 6 0
3 5 3 0
```

With IO:
```
5
2 0 9 0.5 
4 0 7 0.3 
4 0 5 0.2 
3 2 6 0.1 
1 5 3 0.2 
```
