#ifndef MEASURETIME_C
#define MEASURETIME_C

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

/* OSX includes only */
#include <mach/mach_time.h>
#include <mach/mach.h>
#include <mach/thread_policy.h>

#define B __asm__ __volatile__("" ::: "memory")

/* Check the rdtsc register and report the number of clock ticks */
static inline uint64_t rdtsc() {
	uint32_t eax = 0, edx;

	__asm__ __volatile__("cpuid;" "rdtsc;" : "+a" (eax), "=d" (edx) : : "%rcx", "%rbx", "memory");

	__asm__ __volatile__("xorl %%eax, %%eax;" "cpuid;" : : : "%rax", "%rbx", "%rcx", "%rdx", "memory");

	return (((uint64_t)edx << 32) | eax);
}

/* Compute standard of deviation of a list of numbers */
float std(float data[], size_t numElems) {

    float sum = 0.0;
    float mean = 0.0;
    float std = 0.0;
    int i = 0;

    for(; i<numElems; ++i) {
        sum += data[i];
    }

    mean = sum/numElems;

    for(i = 0; i < numElems; ++i)
        std += pow(data[i] - mean, 2);

    return sqrt(std/numElems);
}

/* Prints the header for the output table */
void printHeader(char *title) {
    printf("\n==========%s==========\n", title);
    printf("|==============|============|\n");
    printf("|  Experiment  |  Overhead  |\n");
    printf("|==============|============|\n");
}

/* Prints a single entry of the output table */
void printEntry(int experimentNumber, uint64_t entry) {
    printf("|%*s%-8d| %*s%-9" PRIu64 "|\n", 6, " ", experimentNumber, 2, " ", entry);
}

/* Prints the average and stdev in the format of the output table */
void printStats(float average, float std) {
    printf("|--------------|------------|\n");
    printf("|   Average    | %*s%-10.3f|\n", 1, " ", average);
    printf("|--------------|------------|\n");
    printf("|   Std Dev    | %*s%-10.3f|\n", 1, " ", std);
    printf("|--------------|------------|\n");
}
#endif
