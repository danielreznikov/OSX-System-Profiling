/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.1.3 - Measure the overhead for making a system call.
 */
#include "../utils.h"
#include "driver_1.h"

void measure_systemcall_overhead(uint64_t experiments, uint64_t iterations) {
    int i = 0, j = 0, pid, fds[2];
    uint64_t total = 0;
    struct stat statbuf;
    time_t t;
    double avg, std, aggregate = 0.0;
    double results[experiments];

    printHeader("4.1.3 - System Call Overhead");

    /* Run multiple experiments on this code */
    for (j = 0; j < experiments; j ++) {
        /* Initialize and reset some values */
        i = 0;
        total = 0;

        /* Start the loop for given iterations */
        for (i = 0; i < iterations; i++) {
            /* Create a pipe from child to parent */
            pipe(fds);

            /* Fork and report errors if necessary */
            if ((pid = fork()) == ERR) {
                perror("fork");
                exit(ERR);
            }

            if (!pid) {                 /* Child process will do the system call */
                uint64_t start, end, send;

                close(fds[READ]);

                /* Do system call operation */
                start = rdtsc();
                // fstat(0, &statbuf);
                getpid();
                // time(&t);
                end = rdtsc();

                /* TODO: Will need to subtract the read times later */
                /* TODO: Figure out why first iteration is so much faster */
                send = end - start;

                // printf("in child, send is: %" PRIu64 "\n", send);

                /* Update parent and exit */
                write(fds[WRITE], &send, sizeof(uint64_t));
                close(fds[WRITE]);
                exit(0);
            }
            else {                      /* Parent process will wait for child */
                uint64_t recv;

                close(fds[WRITE]);

                /* Read child execution time and update total */
                read(fds[READ], &recv, sizeof(uint64_t));

                // printf("in parent, recv is: %" PRIu64 "\n", recv);

                /* Don't take into account first iterations since it's so off */
                if (i) {
                    total += recv;
                }

                /* Wait and do clean up */
                wait(&pid);
                close(fds[READ]);
            }
        }

        total = (total) / (double)(iterations - 1);
        total -= READ_TIME_OVERHEAD;
        aggregate += total;
        results[j] = total;

        /* Don't take into account first iterations since it's so off */
        printEntry(j, (double) total);
    }

    stats(results, experiments, &avg, &std);
    printStats((double)aggregate / (double)experiments, std);
}
