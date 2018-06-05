/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * Authors - Daniel Reznikov, Aaron Trefler, Rebecca McKinley
 *
 * Section 4.4.4 - Contention: Report the average time to read one file system block of
 *                 data as a function of the number of processes simultaneously performing
 * 					 the same operation on different files on the same disk (and not in the
 * 					 file buffer cache).
 */

/*
 * Barrier implementation from here: http://blog.albertarmea.com/post/47089939939/using-pthreadbarrier-on-mac-os-x
 */

#include "../utils.h"
#include "driver_4.h"
#include <pthread.h>
#include "Pthread_Barrier.h"

pthread_barrier_t barrier;
int read_size = 4*1024;
int file_size = 512*1024;

/* Each thread will execute this  */
void *run_thread(void *input) {
    int i, fds, file_id, open_ret, offset;
    int blocks_per_file = file_size / read_size;
    char filename[100] = {0}, gen_data_script[100] = {0}, *buf;
    uint64_t start, end, total_time = 0;

    /* Extract this thread's file to read */
    file_id = (int)input;
    sprintf(filename, "data/data_proc%d", file_id);

    /* Generate your test file */
    sprintf(gen_data_script, "sh generate_data.sh %d &>/dev/null", file_id);
    system(gen_data_script);

    /* Open up the file */
    fds = open(filename, O_RDONLY);
    if (fds == ERR) {
       printf("Error opening file %s, error: %s\n", filename, strerror(errno));
    }

    /* Disable the file cache */
    system("sudo purge");

    if (fcntl(fds, F_NOCACHE, 1) == ERR) {
        printf("Did not disable the file cache\n");
    }

    /* Create a buffer for reading 4KB which is one page */
    buf = malloc(sizeof(char) * read_size);

    /* Wait for everyone before doing your reading */
    pthread_barrier_wait(&barrier);

    /* Start the timer and do the read */
    for (i = 0; i < blocks_per_file; i++) {

        offset = -1 * i * read_size;
        lseek(fds, offset, SEEK_END);

        start = rdtsc();
        int status = read(fds, buf, read_size);
        end = rdtsc();


        total_time += end - start;
    }

    /* Free up everything */
    free(buf);
    close(fds);

    /* Delete the file you created */
    remove(filename);

    /* Return how long it took you to read one block */
    return (void *)total_time;
}

/* Driver for Contention experiment */
void measure_read_contention() {
    int proc, total_proc;
    pthread_t *threads;
    void *measured_time, *proc_ndx;
    int blocks_per_file = file_size / read_size;
    uint64_t start, end, total;

    for (total_proc = 0; total_proc < 11; total_proc++) {

        /* Malloc for the number of threads you want */
        threads = (pthread_t *)malloc(sizeof(pthread_t) * total_proc);

        /* Initialize the barrier for all threads */
        pthread_barrier_init(&barrier, NULL, total_proc);

        start = rdtsc();

        /* Start as many threads as you want processors */
        for (proc = 0; proc < total_proc; proc++) {
            pthread_create(threads + proc, NULL, run_thread, (void *)proc);
        }

        /* Join all of the threads */
        for (proc = 0; proc < total_proc; proc++) {
            pthread_join(*(threads + proc), &measured_time);
            // printf("Thread's measured time was: %f micro seconds\n", ((uint64_t)measured_time / (uint64_t)1.8) * 0.001);
            // printf("Thread's measured time was %f ms\n", ((uint64_t)measured_time / (double)blocks_per_file) / (1.8 * pow(10, 6)));
        }

        end = rdtsc();

        total = end - start;
        total -= READ_TIME_OVERHEAD;
        total -= (total_proc * THREAD_CREATE_OVERHEAD);
        total -= (total_proc * THREAD_CONTEXT_SWITCH_OVERHEAD);

        printf("total execution per proc is %f seconds\n", (total / (double)total_proc) / (1.8 * pow(10, 9)));

        free(threads);

        printf("\n\n");
    }
}
