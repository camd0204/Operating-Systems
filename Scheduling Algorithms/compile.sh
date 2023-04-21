gcc -o ./out/round_robin_scheduling_simulator main.c util.c process.c queue.c scheduler.c scheduling_round_robin.c
gcc -o ./out/priority_scheduling_simulator main.c util.c process.c queue.c scheduler.c scheduling_priority.c
gcc -o ./out/shortes_job_scheduling_simulator main.c util.c process.c queue.c scheduler.c scheduling_shortest_job.c