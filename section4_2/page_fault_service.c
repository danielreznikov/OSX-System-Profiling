/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.2.3 - Measure the page fault service time.
 */
#include "../utils.h"
#include "driver_2.h"
#include <assert.h>
#include <unistd.h>


double execute_page_fault(int offset) {
    unsigned int DATA_BYTES = 3221225472;  // based on 3GB random.data file

    double page_fault_time, total_time;
    uint64_t end_time, start_time;
    
    // Get file descriptor
    int fd = open("random.data", O_RDWR);
    if (fd < 0) {
        printf("Failed to open random.data\n");
        return -1;
    }
    
    // Move data into virtual memory using mmap
    void* mmappedData = (char*) mmap(NULL, DATA_BYTES, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    assert(mmappedData != MAP_FAILED);
    char* pointer = (char*) mmappedData;

    // Read data into physical memory, which will induce page faults
    start_time = rdtsc();
    char byte = pointer[offset];
    end_time = rdtsc();
    total_time = end_time - start_time;

    printf("%c", byte);  // Needed to ensure program performs page faults

    // Compute page fault time"
    total_time -= LOOP_OVERHEAD;
    total_time -= READ_TIME_OVERHEAD * 2;
    page_fault_time = total_time;

    // Clean up
    munmap(pointer, DATA_BYTES);
    munmap(mmappedData, DATA_BYTES);
    close(fd);

    // Display results
    return page_fault_time;
}


/* 4.2.3 - Page Fault Service Time */
void measure_page_fault(uint64_t num_experiments, uint64_t iterations) {
    // Hard code these parameters
    iterations = 1;
    num_experiments = 10;

    int STRIDE = 33554432; // 32MB
    unsigned int DATA_BYTES = 3221225472;  // based on 3GB random.data file

    double avg, experiment_time, std;
    double experiment_results [num_experiments];

    printf("Ignore Output: ");
    for (int i = 0; i < num_experiments; i++) {
            experiment_time = execute_page_fault((STRIDE * i) % DATA_BYTES);
        experiment_results[i] = experiment_time;
    }

    printf("\n");
    stats(experiment_results, num_experiments, &avg, &std);
    printStats(avg, std);
    write_results_array("./results/page_fault_service.csv", experiment_results);
}
