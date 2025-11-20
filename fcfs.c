/**
* Finish later
*
*
*
*
*
*/
#include <stdio.h>
#include "scheduler.h"



void fcfs(task_t *task_array, u_int count, const char *file_name) {

    printf("Scheduling Policy: FCFS\n");
    printf("There are %d tasks loaded from \"%s\". Press any key to continue . . .", count, file_name);
    getchar(); /* Wait for character*/
    printf("==================================================================\n");

    int i = 0;
    int time = 0;
    double total_wait = 0.0;
    double total_turn = 0.0;
    double idle_time = 0.0;
    task_t *curr = &task_array[i];

    while (i < count) {
        curr = &task_array[i];
        total_wait += time;
        total_turn += curr->burst_time;
        idle_time += time - curr->arrival_time;
        for (int j = 0; j < curr->burst_time; j++) {
          printf("<time %d> process %d is running", time, curr->pid);
          time++;
        }
        printf("<time %d> process %d is finished . . .", time, curr->pid);
        i++;
    }

    printf("<time %d> all processes finished . . . . . .\n",time);
    printf("==================================================================\n");
    printf("Average waiting time:    %.2f\n", total_wait / count);
    printf("Average response time:    %.2f\n", total_wait / count);
    printf("Average turnaround time:    %.2f\n", total_turn / count);
    printf("Overall CPU usage:    %.2f%%\n", 100 * (total_turn / (total_turn + idle_time)));
    printf("==================================================================\n");

}

