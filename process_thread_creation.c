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
    float exp_total = 0.0, results[experiments], avg, std;

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
        printEntry(exper, (float)itr_total / (float)iterations);
        results[exper] = (float)itr_total / (float)iterations;
    }

    /* Get and print out the stats for this experiment */
    stats(results, experiments, &avg, &std);
    printStats(avg, std);
}

/* Measures the overhead of creating a forked process */
void measure_fork_overhead(uint64_t experiments, uint64_t iterations) {
    uint64_t start, end;
    int exper = 0, iter = 0, itr_total = 0.0, pid, fds[2];
    float exp_total = 0.0, results[experiments], avg, std;

    printHeader("4.4 - Process Creation Overhead");

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
                close(fds[INPUT]);
                write(fds[OUTPUT], &end, sizeof(uint64_t));
                close(fds[OUTPUT]);

                exit(0);
            }
            else {
                /* Do some cleanup and wait for child */
                close(fds[OUTPUT]);
                wait(&pid);

                /* Read from the child and kill the pipe */
                read(fds[INPUT], &end, sizeof(uint64_t));
                close(fds[INPUT]);

                /* Calculate the time to createa a fork */
                itr_total += (uint64_t)end - start;
            }
        }

        /* Save this experimental result into the array */
        printEntry(exper, (float)itr_total / (float)iterations);
        results[exper] = (float)itr_total / (float)iterations;
    }

    /* Get and print out the stats for this set of experiments */
    stats(results, experiments, &avg, &std);
    printStats(avg, std);
}
