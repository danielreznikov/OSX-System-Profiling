/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * Header file that declares all of the 4.1 measurement code.
 */

#ifndef DRIVER_1_H
#define DRIVER_1_H

/* Generic includes */
#include <inttypes.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/* OSX includes only */
#include <mach/mach_time.h>
#include <mach/mach.h>
#include <mach/thread_policy.h>

/* Constants */
#define EXPERIMENTS 10
#define ITERATIONS 10

/* 4.1.1 - Read and Loop Overhead */
void measure_read_overhead(int experiments, int iterations);
void measure_loop_overhead(int experiments, int iterations);

/* 4.1.2 - Procedure Call Overhead */
void measure_procedure_overhead(uint64_t experiments, uint64_t iterations);

/* 4.1.3 - System Call Overhead */
void measure_systemcall_overhead(uint64_t experiments, uint64_t iterations);

/* 4.1.4 - */
void measure_thread_overhead(uint64_t experiments, uint64_t iterations);
void measure_fork_overhead(uint64_t experiments, uint64_t iterations);

/* 4.1.5 - Context Switch Overhead */
void measure_proc_context_switch(uint64_t total_experiments, uint64_t trials);
void measure_thread_context_switch(int total_experiments, int trials);

#endif
