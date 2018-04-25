#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#include "systemcall_overhead.c"
#include "measurement_overhead.c"
#include "procedure_call_overhead.c"
#include "process_thread_creation.c"
#include "utils.c"

#define EXPERIMENTS 10
#define ITERATIONS 10

/* Main driver and formatting for project output */
int main() {
    printf("==========CSE 221 Final Project Measurements==========\n");

    /* 4.1 - Measurement and Loop Overhead */
    readTimeOverhead(EXPERIMENTS, ITERATIONS);
    loopOverhead(EXPERIMENTS, ITERATIONS);

    /* 4.2 - Procedure Call Overhead */
    // run_experiment(0);

    /* 4.3 - System Call Overhead */
    measure_systemcall_overhead(EXPERIMENTS, ITERATIONS);

    /* 4.4 - Process/Thread Creation Overhead */
    measure_thread_overhead(EXPERIMENTS, ITERATIONS);
    measure_fork_overhead(EXPERIMENTS, ITERATIONS);

    return 0;
}
