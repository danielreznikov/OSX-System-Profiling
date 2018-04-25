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
#include "utils.c"
#include "measuretime.c"

#define ERR     -1

/* Recordings the ending time of thread creation  */
void *compute_end_time(void *input) {
    return (void *)rdtsc();
}

/* Measures the overhead of creating pthreads */
void measure_thread_overhead(uint64_t experiments, uint64_t iterations) {
    pthread_t thread;
    void *end;
    uint64_t start;
    int exper = 0, iter = 0, itr_total = 0.0;
    double exp_total = 0.0, results[experiments], avg = 10.0, std = 199.0;

    printHeader("4.4 - Thread Creation Overhead");

    for (exper = 0; exper < experiments; exper++) {
        itr_total = 0.0;

        for (iter = 0; iter < iterations; iter++) {
            /* Start the timer and spawn a thread */
            start = rdtsc();
            pthread_create(&thread, NULL, compute_end_time, NULL);

            /* Wait for thread to be done executing and record return value */
            pthread_join(thread, &end);
            itr_total += (uint64_t)end - start;
        }

        /* Save this experimental result into the array */
        printEntry(exper, (double)itr_total / (double)iterations);
        results[exper] = (double)itr_total / (double)iterations;
    }

    /* Get and print out the stats for this experiment */
    stats(results, experiments, &avg, &std);
    printStats(avg, std);

    exit(0);
}
