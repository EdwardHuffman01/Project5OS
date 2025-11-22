#include <stdio.h>
#include "scheduler.h"

int main(void) {
    task_t tasks[6];

    // Example: 3 processes, all arrive at time 0
    tasks[0].pid = 1;
    tasks[0].arrival_time = 0;
    tasks[0].burst_time = 10;

    tasks[1].pid = 2;
    tasks[1].arrival_time = 0;
    tasks[1].burst_time = 9;

    tasks[2].pid = 3;
    tasks[2].arrival_time = 3;
    tasks[2].burst_time = 5;

    tasks[3].pid = 4;
    tasks[3].arrival_time = 7;
    tasks[3].burst_time = 4;

    tasks[4].pid = 5;
    tasks[4].arrival_time = 10;
    tasks[4].burst_time = 6;

    tasks[5].pid = 6;
    tasks[5].arrival_time = 10;
    tasks[5].burst_time = 7;

    unsigned int time_quantum = 4;

    rr(tasks, 6, time_quantum, "testfile.txt");
    //fcfs(tasks, 3,"testfile.txt");
    return 0;
}
