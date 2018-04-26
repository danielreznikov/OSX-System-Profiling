/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * Main driver file for 4.1 - CPU Measurements.
 */

#include "driver_1.h"

/* Main driver and formatting for project output */
int main() {
    printf("==========CSE 221 Final Project Measurements==========\n");

    /* 4.1.1 - Measurement and Loop Overhead */
    measure_read_overhead(EXPERIMENTS, ITERATIONS);
    measure_loop_overhead(EXPERIMENTS, ITERATIONS);

    /* 4.1.2 - Procedure Call Overhead */
    measure_procedure_overhead(EXPERIMENTS, ITERATIONS);

    /* 4.1.3 - System Call Overhead */
    measure_systemcall_overhead(EXPERIMENTS, ITERATIONS);

    /* 4.1.4 - Process/Thread Creation Overhead */
    measure_thread_overhead(EXPERIMENTS, ITERATIONS);
    measure_fork_overhead(EXPERIMENTS, ITERATIONS);

    /* 4.1.5 - Process/Thread Context Switch Overhead */
    measure_proc_context_switch(EXPERIMENTS, ITERATIONS);
    measure_thread_context_switch(EXPERIMENTS, ITERATIONS);

    return 0;
}
