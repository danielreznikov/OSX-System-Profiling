/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * Header file that declares all of the 4.2 measurement code.
 */

#ifndef DRIVER_2_H
#define DRIVER_2_H

/* Generic includes */
#include <emmintrin.h>
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

/* 4.2.1 - RAM Access Time */
void measure_RAM_access(uint64_t experiments, uint64_t iterations);

/* 4.2.2 - RAM Bandwidth */
void measure_RAM_bandwidth(uint64_t experiments, uint64_t iterations);

/* 4.2.3 - Page Fault Service Time */
void measure_page_fault(uint64_t experiments, uint64_t iterations);

#endif
