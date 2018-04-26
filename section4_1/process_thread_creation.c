/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.1.4 - Measure the overhead for creating a new process (fork) and for
 * creating a new kernel thread (pthread).
 */
#include "../utils.h"
#include "driver_1.h"

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

    printHeader("4.1.4 - Thread Creation Overhead");

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
}

/* Measures the overhead of creating a forked process */
void measure_fork_overhead(uint64_t experiments, uint64_t iterations) {
    uint64_t start, end;
    int exper = 0, iter = 0, itr_total = 0.0, pid, fds[2];
    double exp_total = 0.0, results[experiments], avg, std;

    printHeader("4.1.4 - Process Creation Overhead");

    /* Perform multiple experiments on these iterations */
    for (exper = 0; exper < experiments; exper++) {
        itr_total = 0.0;

        for (iter = 0; iter < iterations; iter++) {
            /* Create a pipe between parent and child */
            pipe(fds);

            /* Start the timer */
            start = rdtsc();

            /* Call the fork to create a new process */
            if (!(pid = fork())) {                          /* In the child */
                /* Take measurement at the very beginning */
                end = rdtsc();

                /* Close for clarity, write time measurement to pipe */
                close(fds[READ]);
                write(fds[WRITE], &end, sizeof(uint64_t));
                close(fds[WRITE]);

                exit(0);
            }
            else {
                /* Do some cleanup and wait for child */
                close(fds[WRITE]);
                wait(&pid);

                /* Read from the child and kill the pipe */
                read(fds[READ], &end, sizeof(uint64_t));
                close(fds[READ]);

                /* Calculate the time to createa a fork */
                itr_total += (uint64_t)end - start;
            }
        }

        /* Save this experimental result into the array */
        printEntry(exper, (double)itr_total / (double)iterations);
        results[exper] = (double)itr_total / (double)iterations;
    }

    /* Get and print out the stats for this set of experiments */
    stats(results, experiments, &avg, &std);
    printStats(avg, std);
}
