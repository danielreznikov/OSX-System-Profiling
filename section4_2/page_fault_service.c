/*
 * Final Project | CSE 221 | Spring 2018 | UCSD
 *
 * 4.2.3 - Measure the page fault service time.
 */
#include "../utils.h"
#include "driver_2.h"
#include <assert.h>

/* 4.2.3 - Page Fault Service Time */
void measure_page_fault(uint64_t experiments, uint64_t iterations) {
    int DATA_BYTES = 1000000; // based on random.data size
    uint64_t strt, end;

    // Get file descriptor
    int fd = open("random.data", O_RDONLY);

    // For each experiment
    for (int i = 0; i < experiments; i++) {

        // Move data into virtual memory using mmap
        void* mmappedData = mmap(NULL, DATA_BYTES, PROT_NONE, MAP_SHARED, fd, 0);
        assert(mmappedData != MAP_FAILED);
        char *pointer = mmappedData;

            // Read data into physical memory, which will induce page faults
            for (int j = 0; j < 10; j++) {
                strt = rdtsc();
                char byte = pointer[0];
                end = rdtsc();

                // seek(page size + 1) or seek(page size + 1)
            }

            // Compute page fault time = total pages / total cycles

            // Save results

        // Remove data from memory and virtual memory
    }

    // Output results

}

// int main() {
//     measure_page_fault(1, 10);
//     return 0;
// }
