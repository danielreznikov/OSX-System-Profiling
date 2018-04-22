#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "measuretime.c"

#define ITERATIONS  1000
#define INPUT       0
#define OUTPUT      1
#define ERR         -1

int main() {
    int i = 0, pid, fds[2];
    uint64_t total;
    struct stat statbuf;
    time_t t;

    /* Start the loop for given iterations */
    for (i = 0; i < ITERATIONS; i++) {
        /* Create a pipe from child to parent */
        pipe(fds);

        /* Fork and report errors if necessary */
        if ((pid = fork()) == ERR) {
            perror("fork");
            exit(ERR);
        }

        if (!pid) {                 /* Child process will do the system call */
            uint64_t start, end, send;

            close(fds[INPUT]);

            /* Do system call operation */
            start = rdtsc();
            fstat(0, &statbuf);
            // getpid();
            // time(&t);
            end = rdtsc();

            /* TODO: Will need to subtract the read times later */
            /* TODO: Figure out why first iteration is so much faster */
            send = end - start;

            // printf("in child, recv is: %" PRIu64 "\n", send);

            /* Update parent and exit */
            write(fds[OUTPUT], &send, sizeof(uint64_t));
            close(fds[OUTPUT]);
            exit(0);
        }
        else {                      /* Parent process will wait for child */
            uint64_t recv;

            close(fds[OUTPUT]);

            /* Read child execution time and update total */
            read(fds[INPUT], &recv, sizeof(uint64_t));

            /* Don't take into account first iterations since it's so off */
            if (i) {
                total += recv;
            }

            /* Wait and do clean up */
            wait(&pid);
            close(fds[INPUT]);
        }
    }

    /* Don't take into account first iterations since it's so off */
    printf("Average execution time is: %" PRIu64 "\n", total / (uint64_t)(ITERATIONS - 1));

    return 0;
}
