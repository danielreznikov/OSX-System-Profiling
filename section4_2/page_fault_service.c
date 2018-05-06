/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.2.3 - Measure the page fault service time.
 */
#include "../utils.h"
#include "driver_2.h"
#include <assert.h>
#include <unistd.h>


static inline uint64_t rdtsc_v2(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}


/* 4.2.3 - Page Fault Service Time */
void measure_page_fault(uint64_t num_experiments) {
    unsigned int DATA_BYTES = 1048576; // based on 1MB random.data file
    
    float experiment_results [num_experiments];
    int offset = 0;
    int total_time;
    uint64_t end_time, start_time; 

    // Compute memory page information
    int page_size = getpagesize();
    int pages_to_read = DATA_BYTES / page_size;

    // Get file descriptor
    int fd = open("random.data", O_RDWR);

    // Run an experiment
    for (int i = 0; i < num_experiments; i++) {
        offset = 0;
        total_time = 0;
        
        // Move data into virtual memory using mmap
        void* mmappedData = mmap(NULL, DATA_BYTES, PROT_NONE, MAP_SHARED, fd, 0);
        assert(mmappedData != MAP_FAILED);
        char *pointer = mmappedData;

        // Read data into physical memory, which will induce page faults
        for (int j = 0; j < pages_to_read; j++) {
            start_time = rdtsc();
            char byte = pointer[(offset + 1)];
            end_time = rdtsc();
            total_time += end_time - start_time;
            
            offset += page_size;
        }

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
    write_results_array("results/procedure_call_overhead.csv", experiment_results);
}

/*
int main() {
    measure_page_fault(1);
    return 0;
}
*/
