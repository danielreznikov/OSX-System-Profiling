/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * Header file that declares all of the 4.4 measurement code.
 */

#ifndef DRIVER_4_H
#define DRIVER_4_H

/* Generic includes */
#include <emmintrin.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
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
#define EXPERIMENTS     10
#define ITERATIONS      10

/* 4.4.1 - RAM Access Time */
void measure_file_cache();

/* 4.4.2 - File Read Time */
void file_read_time();

/* 4.4.3 - Remote File Read Time */
void remote_file_read_time();

/* 4.4.4 - Contention */
void contention();

#endif
