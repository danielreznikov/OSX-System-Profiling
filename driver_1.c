/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * Main driver file for 4.1 - CPU Measurements.
 */

#include "driver_1.h"

#define EXPERIMENTS 10
#define ITERATIONS 10

/* Main driver and formatting for project output */
int main() {
    printf("==========CSE 221 Final Project Measurements==========\n");

    /* 4.1.1 - Measurement and Loop Overhead */
    readTimeOverhead(EXPERIMENTS, ITERATIONS);
    loopOverhead(EXPERIMENTS, ITERATIONS);

    /* 4.1.2 - Procedure Call Overhead */
    run(EXPERIMENTS, ITERATIONS);

    /* 4.1.3 - System Call Overhead */
    measure_systemcall_overhead(EXPERIMENTS, ITERATIONS);

    /* 4.1.4 - Process/Thread Creation Overhead */
    measure_thread_overhead(EXPERIMENTS, ITERATIONS);
    measure_fork_overhead(EXPERIMENTS, ITERATIONS);

    /* 4.1.5 - Process/Thread Context Switch Overhead */
    process_contextswitch_exps(10, 10);
    thread_contextswitch_exps(10, 10);

    return 0;
}
