/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.2.3 - Measure the page fault service time.
 */
#include "../utils.h"
#include "driver_2.h"
#include <assert.h>
#include <unistd.h>


/* 4.2.3 - Page Fault Service Time */
void measure_page_fault(uint64_t num_experiments) {
    unsigned int DATA_BYTES = 3221225472;  // based on 3GB random.data file
    
    float experiment_results [num_experiments];
    int offset = 33554432;  // 32MB
    int stride = 16777216;  // 16MB
    int pages_to_read = 100;
    int access_idx, total_time;
    uint64_t end_time, start_time; 
    

    // Get file descriptor
    int fd = open("random.data", O_RDONLY);
    if (fd < 0) {
        printf("Failed to open random.data\n");
        return;
    }

    // Run an experiment
    for (int i = 0; i < num_experiments; i++) {
        offset = 0;
        total_time = 0;
        
        // Move data into virtual memory using mmap
        void* mmappedData = mmap(NULL, DATA_BYTES, PROT_NONE, MAP_SHARED, fd, 0);
        assert(mmappedData != MAP_FAILED);
        char *pointer = mmappedData;

        // Read data into physical memory, which will induce page faults
        start_time = rdtsc();
        for (int j = 0; j < pages_to_read; j++) {
            char byte = pointer[(((offset + j) * stride) % (DATA_BYTES - 1))];
            //printf("test\n");
        }
        end_time = rdtsc();
        total_time += end_time - start_time;

        // Compute average page fault time"
        /* 
        Uncomment when numbers are accurate for system running
        total_time -= LOOP_OVERHEAD;
        total_time -= READ_TIME_OVERHEAD * 2 * pages_to_read;
        */
        experiment_results[i] = total_time / pages_to_read;

        // Remove data from virtual memory
        munmap(pointer, DATA_BYTES);
        munmap(mmappedData, DATA_BYTES);

    }
    close(fd);

    // Write out results
    printf("Page Fault Time: %f\n", experiment_results[0]);
    //write_results_array("results/page_fault_service.csv", experiment_results);
}