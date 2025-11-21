/*
*
*
*
*
*
*
*/

#include <stdio.h>
#include "scheduler.h"

static void print_header(u_int count, const char *file_name, u_int time_quantum){
    printf("Scheduling Policy: RR\n");
    printf("There are %u tasks loaded from \"%s\". Press ENTER to continue...", count, file_name);
    getchar(); /* Wait for character*/
    printf("==================================================================\n");
}

static void print_footer(double total_turn, double total_wait, double cpu_time, double idle_time, u_int count, u_int time){
    printf("<time %u> All processes finished......\n",time);
    printf("==================================================================\n");
    printf("Average waiting time:    %.2f\n", total_wait / count);
    printf("Average response time:    %.2f\n", total_wait / count);
    printf("Average turnaround time:    %.2f\n", total_turn / count);
    printf("Overall CPU usage:    %.2f%%\n", 100 * cpu_time / (cpu_time + idle_time));
    printf("==================================================================\n");
}

void rr(task_t *task_array, u_int count, u_int time_quantum, const char *file_name){

    u_int i = 0;
    u_int time = 0;
    u_int finish_count = 0;
    double total_wait = 0.0;
    double total_turn = 0.0;
    double idle_time = 0.0;
    double cpu_time = 0.0;
    task_t *task;
    u_int remaining_burst[count];
    u_int wait_time[count];
    u_int execution_time[count];

    print_header(count, file_name, 2);

    if(time_quantum <= 0){
        printf("\nTime quantum must be greater than zero.\n\n");
        return;
    }

    /* initalize the remaining burst times in the array */
for (u_int k = 0; k < count; k++) {
    remaining_burst[k] = task_array[k].burst_time;
}


    while(finish_count < count){
        task = &task_array[i];
       // wait_time[i] = time - wait_time[i];
    

        if(remaining_burst[i] != 0){
            
            for(u_int j = 0; j < time_quantum && remaining_burst[i] != 0; j++){
                //execution_time[i]++;
                printf("<time %u> process %u is running\n", time, task->pid);
                remaining_burst[i] = remaining_burst[i] - 1;
                time++;
            }
            if (remaining_burst[i] == 0) {
                printf("<time %u> process %u is finished...\n", time, task->pid);
                finish_count++;
            }
        }

      //  wait_time[i] += time - wait_time[i];


        i++;

        if(i == count){
            i = 0;
        }

    }
}