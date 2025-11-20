/*
 * COMP 3500: Project 5 Scheduling
 * Xiao Qin
 * Version 1.0  11/18/2019
 *
 * This source code shows how to conduct separate compilation.
 *
 * How to compile using Makefile?
 * $make
 *
 * How to manually compile?
 * $gcc -c open.c
 * $gcc -c read.c
 * $gcc -c print.c
 * $gcc open.o read.o print.o scheduler.c -o scheduler
 *
 * How to run?
 * Case 1: no argument. Sample usage is printed
 * $./scheduler
 * Usage: scheduler <file_name>
 *
 * Case 2: file doesn't exist.
 * $./scheduler file1
 * File "file1" doesn't exist. Please try again...
 *
 * Case 3: Input file
 * $./scheduler task.list
 * data in task.list is printed below...
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "print.h"
#include "open.h"
#include "read.h"

int main(int argc, char *argv[]) {
    char *file_name = argv[1];
    FILE *fp; /* file descriptor */
    task_t task_array[MAX_TASK_NUM];

    int error_code;
    u_int count;

    /* Expected:
       argv[0] = scheduler
       argv[1] = task_list_file
       argv[2] = policy (FCFS | RR | SRTF)
       argv[3] = time_quantum (only if policy == RR)
    */


    if (argc < 3) {
        printf("Usage: %s task_list_file [FCFS|RR|SRTF] [time_quantum]\n", argv[0]);
        return EXIT_FAILURE;
    }

   

    error_code = open_file(argv[1], &fp);
    if (error_code == 1) return EXIT_FAILURE;
    
    read_file(fp, task_array, &count);
    print_task_list(task_array, count);
    fclose(fp);
  

    if(strcmp(argv[2], "FCFS") == 0) {
        fcfs(task_array, count, file_name);
    }

    else if(strcmp(argv[2], "RR") == 0) {

        if (argc != 4) {
        fprintf(stderr,
            "Usage (RR): %s task_list_file RR time_quantum\n", argv[0]);
        return EXIT_FAILURE;
        }

        int time_quantum = atoi(argv[3]);
        if (time_quantum <= 0) {
        fprintf(stderr, "time_quantum must be a positive integer\n");
        return EXIT_FAILURE;
        }

        rr(task_array, count, time_quantum);
    }

    else if(strcmp(argv[2], "SRTF") == 0) {
        srtf(task_array, count);
    }

    else{
        printf("Unknown scheduling policy %s.\n", argv[2]);
        return EXIT_FAILURE;
    }

   
   return EXIT_SUCCESS;

    
}
