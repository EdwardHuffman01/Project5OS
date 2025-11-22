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

    if(time_quantum == 0){
        printf("\nTime quantum must be greater than zero.\n\n");
        return;
    }

    /* initalize the remaining burst times in the array */
    for (u_int k = 0; k < count; k++) {
      remaining_burst[k] = task_array[k].burst_time;
      has_started[k] = 0;
    }


    while (finish_count < count) {

    /* If no ready tasks, jump to next arrival and admit all at that time */
    if (queue_size == 0) {
        if (next_avaliable < count) {
            time = task_array[next_avaliable].arrival_time;
            while (next_avaliable < count &&
                   task_array[next_avaliable].arrival_time <= time) {
                ready[tail] = next_avaliable;
                tail = (tail + 1) % count;
                queue_size++;
                next_avaliable++;
                // optional debug: printf("Made it into queue %u!\n", next_avaliable);
            }
        } else {
            /* nothing left to arrive and queue is empty */
            break;
        }
    }

    /* Now queue_size > 0: dequeue head */
    u_int i = ready[head];
    head = (head + 1) % count;
    queue_size--;

    task = &task_array[i];

    /* First response time */
    if (!has_started[i]) {
        response_time[i] = time - task->arrival_time;
        total_resp += (double)response_time[i];
        has_started[i] = 1;
    }

    /* Run for up to 'time_quantum' */
    u_int ran = 0;
    for (u_int j = 0; j < time_quantum && remaining_burst[i] > 0; j++) {
        printf("<time %u> process %u is running\n", time, task->pid);
        remaining_burst[i]--;
        time++;
        ran++;
    }
    cpu_time += ran;

    /* AFTER running, admit any tasks that arrived during this slice */
    while (next_avaliable < count &&
           task_array[next_avaliable].arrival_time <= time) {
        ready[tail] = next_avaliable;
        tail = (tail + 1) % count;
        queue_size++;
        next_avaliable++;
        // optional debug: printf("Made it into queue %u!\n", next_avaliable);
    }

    /* Finished or re-enqueue */
    if (remaining_burst[i] == 0) {
        printf("<time %u> process %u is finished...\n", time, task->pid);
        finish_count++;

        total_turn += (double)(time - task->arrival_time);
        total_wait += (double)(time - task->arrival_time - task->burst_time);
    } else {
        ready[tail] = i;
        tail = (tail + 1) % count;
        queue_size++;
    }
}




            
    

    print_footer(total_turn, total_wait,total_resp, cpu_time, idle_time, count, time);
}
