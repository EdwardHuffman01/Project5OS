/*
* COMP 3500: Project 5 Scheduling
* Alex Huffman
* Version 1.0 11/20/25
*
* This source code handles the first come first serve
*  scheduling policy.
*
*/
#include <stdio.h>
#include "scheduler.h"


/* Prints the header of the process simulation */
static void print_header(u_int count, const char *file_name){
  printf("Scheduling Policy: FCFS\n");
    printf("There are %u tasks loaded from \"%s\". Press ENTER to continue...", count, file_name);
    getchar(); /* Wait for character*/
    printf("==================================================================\n");
}

/* Prints the footer of the process simulation */
static void print_footer(double total_turn, double total_wait, double cpu_time, double idle_time, u_int count, u_int time){
   printf("<time %u> All processes finished......\n",time);
    printf("==================================================================\n");
    printf("Average waiting time:    %.2f\n", total_wait / count);
    printf("Average response time:    %.2f\n", total_wait / count);
    printf("Average turnaround time:    %.2f\n", total_turn / count);
    printf("Overall CPU usage:    %.2f%%\n", 100 * cpu_time / (cpu_time + idle_time));
    printf("==================================================================\n");
}

void fcfs(task_t *task_array, u_int count, const char *file_name) {

    u_int i = 0;
    u_int time = 0;
    double total_wait = 0.0;
    double total_turn = 0.0;
    double idle_time = 0.0;
    double cpu_time = 0.0;
    task_t *task;

    print_header(count, file_name);

    while (i < count) {

        task = &task_array[i];

        /* Checks to see if cpu idles before beginning execution */
        if(time < task->arrival_time){
          idle_time += task->arrival_time - time;
          time = task->arrival_time;
        }

        total_wait += time - task->arrival_time;

        for (u_int j = 0; j < task->burst_time; j++) {
          printf("<time %u> process %u is running\n", time, task->pid);
          time++;
        }

        printf("<time %u> process %u is finished...\n", time, task->pid);

        total_turn += time - task->arrival_time;

        i++;
    }
    /* After all process conclude calculate on time spent executing */
    cpu_time = total_turn - total_wait;

   print_footer(total_turn, total_wait, cpu_time, idle_time,count,time);

}

