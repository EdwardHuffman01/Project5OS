/*
* COMP 3500: Project 5 Scheduling
* Alex Huffman
* Version 1.0 11/21/25
*
* This source code handles the round robin scheduling
*   policy
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

static void print_footer(double total_turn, double total_wait, double total_resp, double cpu_time, double idle_time, u_int count, u_int time){
    printf("<time %u> All processes finished......\n",time);
    printf("==================================================================\n");
    printf("Average waiting time:    %.2f\n", total_wait / count);
    printf("Average response time:    %.2f\n", total_resp / count);
    printf("Average turnaround time:    %.2f\n", total_turn / count);
    printf("Overall CPU usage:    %.2f%%\n", 100 * cpu_time / (cpu_time + idle_time));
    printf("==================================================================\n");
}

void rr(task_t *task_array, u_int count, u_int time_quantum, const char *file_name) {

  
    u_int time = 0;
    u_int finish_count = 0;
   
    double total_wait = 0.0;
    double total_turn = 0.0;
    double total_resp = 0.0;
    double idle_time = 0.0;
    double cpu_time = 0.0;

    task_t *task;

    /* Arrays used to calculate averages at the end */
    u_int has_started[count];
    u_int response_time[count];
    u_int remaining_burst[count];

    /* The ready queue */
    u_int ready[count];
    u_int head = 0;
    u_int tail = 0;
    u_int queue_size = 0;
    u_int next_avaliable = 0;
    
    print_header(count, file_name, 2);

    if(time_quantum <= 0){
        printf("\nTime quantum must be greater than zero.\n\n");
        return;
    }

    /* initalize the remaining burst times in the array */
    for (u_int k = 0; k < count; k++) {
      remaining_burst[k] = task_array[k].burst_time;
      has_started[k] = 0;
    }


    while (finish_count < count) {

      while (next_avaliable < count &&
             task[next_avaliable].arrival_time <= time) {
            tail = (tail + 1) % count;
            ready[tail] = next_avaliable;
            queue_size++;
            next_avaliable++;
        } 

        if (queue_size == 0) {
            idle_time += task[next_avaliable].arrival_time - time;
            time = task[next_avaliable].arrival_time;
            printf("<time %u> No process avaliable, idling...\n", time);
            continue;
        }

        u_int i = ready[head];
        head = (head + 1) % count;
        queue_size--;

        task = 
        
        if(remaining_burst[i] != 0){

          if (!has_started[i]) {
            response_time[i] = time - task->arrival_time;
            total_resp += (double)response_time[i];
            has_started[i] = 1;
            }
          
            for(u_int j = 0; j < time_quantum && remaining_burst[i] != 0; j++){
                //execution_time[i]++;
                printf("<time %u> process %u is running\n", time, task->pid);
                remaining_burst[i]--;
                time++;
                cpu_time++;
                }
                if (remaining_burst[i] == 0) {
                    printf("<time %u> process %u is finished...\n", time, task->pid);
                    finish_count++;

                    total_turn += time - task->arrival_time;
                    total_wait += time - task->arrival_time - task->burst_time;
                }
            }

        //  wait_time[i] += time - wait_time[i];


            i++;
            not_ready = 0;
    }

    print_footer(total_turn, total_wait,total_resp, cpu_time, idle_time, count, time);
}
