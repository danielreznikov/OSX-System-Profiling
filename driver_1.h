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

/* 4.1.1 - Read and Loop Overhead */
void readTimeOverhead(int experiments, int iterations);
void loopOverhead(int experiments, int iterations);

/* 4.1.2 - Procedure Call Overhead */
void run(uint64_t experiments, uint64_t iterations);

/* 4.1.3 - System Call Overhead */
void measure_systemcall_overhead(uint64_t experiments, uint64_t iterations);

/* 4.1.4 - */
void measure_thread_overhead(uint64_t experiments, uint64_t iterations);
void measure_fork_overhead(uint64_t experiments, uint64_t iterations);

/* 4.1.5 - Context Switch Overhead */
void process_contextswitch_exps(uint64_t total_experiments, uint64_t trials);
void thread_contextswitch_exps(int total_experiments, int trials);

#endif
