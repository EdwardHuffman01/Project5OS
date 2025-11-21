#include <stdio.h>
#include "scheduler.h"

int main(void) {
    task_t tasks[3];

    // Example: 3 processes, all arrive at time 0
    tasks[0].pid = 1;
    tasks[0].arrival_time = 2;
    tasks[0].burst_time = 3;

    tasks[1].pid = 2;
    tasks[1].arrival_time = 6;
    tasks[1].burst_time = 5;

    tasks[2].pid = 3;
    tasks[2].arrival_time = 8;
    tasks[2].burst_time = 2;

    unsigned int time_quantum = 2;

    rr(tasks, 3, time_quantum, "testfile.txt");
    //fcfs(tasks, 3,"testfile.txt");
    return 0;
}
